#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    Hit hit;
	double t;
	double distance;
    vec3 eMinC;
	eMinC = (ray.endpoint - center);

    double discriminant = pow(dot(ray.direction,eMinC),2) - (dot(ray.direction,ray.direction)*(dot(eMinC,eMinC)-pow(radius,2)));

	if (discriminant < 0)
	{
		hit.object = NULL;
		hit.dist = -1;
		return hit;
	}
	else if (discriminant == 0)
	{
		t = -(dot(ray.direction,eMinC)) / (dot(ray.direction,ray.direction));
		hit.part = part;
		vec3 point = ray.Point(t);
		distance = sqrt(pow(point[0] - ray.endpoint[0],2) + pow(point[1] - ray.endpoint[1],2) + pow(point[2] - ray.endpoint[2],2));
		hit.dist = distance;
		hit.object = new Sphere(center,radius); 
	}
	else
	{
		t = (-(dot(ray.direction,eMinC)) - sqrt(discriminant)) / (dot(ray.direction,ray.direction));
		hit.part = part;
		vec3 point = ray.Point(t);
		distance = sqrt(pow(point[0] - ray.endpoint[0],2) + pow(point[1] - ray.endpoint[1],2) + pow(point[2] - ray.endpoint[2],2));
		hit.dist = distance;
		hit.object = new Sphere(center,radius); 
	}
	
	
    return hit;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;

    //TODO; // compute the normal direction
	normal = (point - center);
    normal[0] *= 2;
	normal[1] *= 2;
	normal[2] *= 2;
	return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    //TODO; // calculate bounding box
	vec3 rad;
	red[0] = radius;
	red[1] = radius;
	red[2] = radius;
	box.lo = center - rad;
	box.hi = center + rad;
    return box;
}
