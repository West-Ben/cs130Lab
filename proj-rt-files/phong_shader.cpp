#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
    //TODO; //determine the color
	for (int i = 0; i < world.lights.size(); i++)
	{
		Ray lightRay(intersection_point,(world.lights[i]->position - intersection_point).normalized());
		Hit hit = world.Closest_Intersection(lightRay);
		if (hit.object == NULL)
		{
			vec3 h = (ray.direction + lightRay.direction).normalized();
			color += ( color_ambient * world.lights[i]->Emitted_Light(lightRay.direction)) 
			+ (world.lights[i]->Emitted_Light(lightRay.direction) * color_diffuse * max((double)0,(double)dot(normal,lightRay.direction)))
			+ (world.lights[i]->Emitted_Light(lightRay.direction) * color_specular * max((double)0,(double)dot(h,ray.direction)));
		}
	}
	
    return color;
}
