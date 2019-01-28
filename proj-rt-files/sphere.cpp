#include "sphere.h"
#include "ray.h"
using namespace std;
// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    Hit hit;
    vec3 eMinC;
	eMinC = (ray.endpoint - center);

	double discriminant = pow(dot(ray.direction,eMinC),2) - (dot(ray.direction,ray.direction)*(dot(eMinC,eMinC) - pow(radius,2)));
	
	if (discriminant <= 0)
	{
		hit.object = NULL;
		return hit;
	}
	else
	{
		double tmin = ((-1 * dot(ray.direction,eMinC) / dot(ray.direction,ray.direction)) - (sqrt(discriminant)) / (dot(ray.direction,ray.direction)));
		double tplus = ((-1 * dot(ray.direction,eMinC) / dot(ray.direction,ray.direction)) + (sqrt(discriminant)) / (dot(ray.direction,ray.direction)));
	
		hit.part = part;
		
		if (tmin > -5 && tmin < tplus)
		{
			hit.dist = tmin;
		}
		else if (tplus > -5)
		{
			hit.dist = tplus;
		}
		hit.object = this;
		
	}
	
    return hit;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
//	cout << "sphere normal" << endl;
    vec3 normal;
//	cout << "start sphere normal" << endl;
    //TODO; // compute the normal direction
	normal = (point - center);
	return normal.normalized();
//	cout << "end sphere normal" << endl;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    //TODO; // calculate bounding box
	vec3 rad;
	rad[0] = radius;
	rad[1] = radius;
	rad[2] = radius;
	box.lo = center - rad;
	box.hi = center + rad;
    return box;
}
