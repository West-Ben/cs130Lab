#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color = color_ambient + render_world.lights[i].Emitted_Light(lightRay) ;
	vec3 h = (ray + lightRay).normalized();
    //TODO; //determine the color
	for (int i = 0; i < render_world.lights.size(); i++)
	{
		Ray lightRay(intersection_point,(render_world.lights[i].position - intersection_point).normalized());
		Hit hit = render_world.Closest_Intersection(lightRay);.
		if (hit.dist < )
		if (hit.object == NULL)
		{
			color += (render_world.lights[i].Emitted_Light(lightRay) * color_diffuse * max(0,dot(normal,lightRay)))
			+ (render_world.lights[i].Emitted_Light(lightRay) * color_specular * max(0,dot(h,ray)));
		}
	}
	
    return color;
}
