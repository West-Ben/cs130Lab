#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color = shader->Shade_Surface(ray,intersection_point,normal,1);
    //TODO;determine color
    
    Ray r;
    r.endpoint = intersection_point;
    r.direction = (ray.direction) - (2 * dot(ray.direction,normal) * normal);
    
    Hit hit = world.Closest_Intersection(r);
    
    if(hit.object == NULL || recursion_depth == 1)
    {
       return  color;
    } 
    else
    {
	vec3 point = r.Point(hit.dist);
	
    	return color += (reflectivity * Shade_Surface(r,point,hit.object->Normal(point,hit.part),(recursion_depth - 1)));
    }
}
