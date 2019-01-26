#include "plane.h"
#include "ray.h"
#include <cfloat>
#include <limits>
using namespace std;
// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray& ray, int part) const
{
    //TODO;
    //	cout << "plane intersection " << endl;
	Hit hit;
	if (dot(normal,ray.direction) == 0)
	{
		hit.object = NULL;
		hit.dist = 0;
		hit.part = part;
		return hit;
	}
	
	double distance = sqrt(pow(x1[0] - ray.endpoint[0],2) + pow(x1[1] - ray.endpoint[1],2) + pow(x1[2] - ray.endpoint[2],2));
	double t = -(dot(normal,ray.endpoint) + distance)/(dot(normal,ray.direction));
	
	if (t < 0)
	{
		hit.object = NULL;
		hit.dist = 0;
		hit.part = part;
	}
	else
	{
		hit.object = this;
		hit.dist = t;
		hit.part = part;
	}
	cout << "return dist = " << hit.dist << endl;
    return hit;
}

vec3 Plane::Normal(const vec3& point, int part) const
{
//	cout << "getting plane normal" << endl;
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
