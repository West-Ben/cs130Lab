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
	normal.normalized();
	ray.direction.normalized();

	color = ( color_ambient * world.ambient_intensity);
    //TODO; //determine the color

	for (int i = 0; i < world.lights.size(); i++)
	{
		Ray lightRay(intersection_point,(world.lights[i]->position - intersection_point).normalized());
		Hit hit = world.Closest_Intersection(lightRay);

		double dropoff  = ((double)(1/(intersection_point - world.lights[i]->position).magnitude_squared()) * world.lights[i]->Emitted_Light(lightRay.direction).magnitude());
		
		if (hit.object == NULL)
		{
			vec3 h = ((((double)-1) * ray.direction) + lightRay.direction).normalized();
			vec3 L = (world.lights[i]->Emitted_Light(lightRay.direction) * ((color_diffuse * max((double)0,(double)dot(normal,lightRay.direction))) + (color_specular * pow(max((double)0,(double)dot(h,ray.direction)),specular_power))));
			color = dropoff * L;
		}	
	}
	
    return color;
}
