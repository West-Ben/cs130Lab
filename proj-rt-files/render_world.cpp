#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"
using namespace std;
extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
	double min_t = (1.8 * pow(10,300));
	Hit hit;
	hit.object = NULL;
	hit.dist = min_t;
	hit.part = 0;	
	for(int i = 0; i < objects.size(); i++)
	{	
		for ( int j = 0; j < objects[i]->number_parts; j++)
		{
			Hit intersect = objects[i]->Intersection(ray,j);
			if(intersect.object != NULL && intersect.dist > 0  && intersect.dist < hit.dist)
			{
				hit = intersect;		
			}
		}
	}	
    return hit;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
	//TODO; // set up the initial view ray here
	vec3 worldPos = (camera.World_Position(pixel_index) - camera.position);
	worldPos.normalized();

    Ray ray(camera.position,worldPos);
    vec3 color=Cast_Ray(ray,recursion_depth_limit);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    vec3 color;
    //TODO; // determine the color here
	
	Hit hit = Closest_Intersection(ray);

	vec3 point = ray.Point(hit.dist);	
	if (hit.object != NULL && recursion_depth > 0)
	{
		color = hit.object->material_shader->Shade_Surface(ray,ray.Point(hit.dist),hit.object->Normal(ray.Point(hit.dist),hit.part),recursion_depth);

	}
	else
	{
		vec3 zero;

		zero[0] = 0;
		zero[1] = 0;
		zero[2] = 0;
		color = background_shader->Shade_Surface(ray,zero,zero,0);
	}
    return color;
}

void Render_World::Initialize_Hierarchy()
{
    //TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.
	 
	for (int i = 0; i < objects.size();i++)
	{
		for (int j = 0; j < objects[i]->number_parts; j++)
		{
			Entry ent;
			ent.obj = objects[i];
			ent.part = j;
			ent.box = objects[i]->Bounding_Box(j);
			hierarchy.entries.push_back(ent);
		}
	}
	
    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
