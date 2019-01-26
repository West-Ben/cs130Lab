#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color = [0,0,0];
    //TODO; //determine the color
	for (int i = 0; i < lights.size(); i++)
	{
		Ray lightRay(intersection_point,(lights[i].position - intersection_point).normalized());
		Hit hit = render_world.Closest_Intersection(lightRay);
		if (hit.object == NULL)
		{
			vec3 h = (ray + lightRay).normalized();
			color += ( color_ambient * lights[i].Emitted_Light(lightRay)) 
			+ (lights[i].Emitted_Light(lightRay) * color_diffuse * max(0,dot(normal,lightRay)))
			+ (lights[i].Emitted_Light(lightRay) * color_specular * max(0,dot(h,ray)));
		}
	}
	
    return color;
}
