#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"
using namespace std;

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
		
	color = (color_ambient *  world.ambient_color * world.ambient_intensity);
    //TODO; //determine the color

	for (int i = 0; i < world.lights.size(); i++)
	{
		Ray shadowRay(intersection_point,(world.lights[i]->position - intersection_point));
		Hit hit;
		hit.object = NULL;
		
		if (world.enable_shadows){
			hit = world.Closest_Intersection(shadowRay);
		}
		double DIntToLight = (world.lights[i]->position - intersection_point).magnitude();
		if (hit.object == NULL || DIntToLight < hit.dist)
		{
			//double dropoff  = (double)(1/(intersection_point - world.lights[i]->position).magnitude_squared());
			vec3 r = (2 * dot(shadowRay.direction,normal) * normal) - (shadowRay.direction);
			vec3 L = (world.lights[i]->Emitted_Light(world.lights[i]->position - intersection_point)) * ((color_diffuse * max((double)0,(double)dot(normal,(world.lights[i]->position - intersection_point).normalized()))) + (color_specular * pow(max((double)0,(double)dot(((double)-1 * ray.direction),r)),specular_power)));
			color += L;

		}	
	}
	
    return color;
}
