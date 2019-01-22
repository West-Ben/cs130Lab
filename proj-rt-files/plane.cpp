#include "plane.h"
#include "ray.h"
#include <cfloat>
#include <limits>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray& ray, int part) const
{
    //TODO;
	Hit hit;
	if (dot(normal,ray.direction) == 0)
	{
		hit.object = NULL;
		hit.dist = -1;
		hit.part = part;
		return hit;
	}
	
	distance = sqrt(pow(x1[0] - ray.endpoint[0],2) + pow(x1[1] - ray.endpoint[1],2) + pow(x1[2] - ray.endpoint[2],2));
	double t = -(dot(normal,ray.endpoint) + distance)/(dot(normal,ray.direction));
	
	vec3 point = ray.point(t);
	if (t < 0)
	{
		hit.object = NULL;
		hit.dist = -1;
		hit.part = part;
	}
	else
	{
		hit.object = new Plane(x1,normal);
		hit.dist = sqrt(pow(point[0] - ray.endpoint[0],2) + pow(point[1] - ray.endpoint[1],2) + pow(point[2] - ray.endpoint[2],2));
		hit.part = part;
	}
	
    return hit;
}

vec3 Plane::Normal(const vec3& point, int part) const
{
    return normal;
}

// There is not a good answer for the bounding box of an infinite object.
// The safe thing to do is to return a box that contains everything.
Box Plane::Bounding_Box(int part) const
{
    Box b;
    b.hi.fill(std::numeric_limits<double>::max());
    b.lo=-b.hi;
    return b;
}
