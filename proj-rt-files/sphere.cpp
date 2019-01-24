#include "sphere.h"
#include "ray.h"
using namespace std;
// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
	cout << "start sphere intersection" << endl;
    Hit hit;
	double t;
	double distance;
    vec3 eMinC;
	cout << endl;
	cout << "endpoint = " << ray.endpoint << endl;
	cout << "center = " << center << endl;
	cout << "ray direction = " << ray.direction << endl;
	cout << "radius = " << radius << endl;
	cout << endl;
	eMinC = (ray.endpoint - center);

    double discriminant = pow(dot(ray.direction,eMinC),2) - (dot(ray.direction,ray.direction)*(dot(eMinC,eMinC) - pow(radius,2)));
	cout << "discriminant = " << discriminant << endl;
	cout << endl;
	
	if (discriminant < 0)
	{
		cout << "no intersection" << endl;
		hit.object = NULL;
		return hit;
	}
	else if (discriminant == 0)
	{
		t = -(dot(ray.direction,eMinC)) / (dot(ray.direction,ray.direction));
		cout << "single contact t = " << t << endl; 
		hit.part = part;
		vec3 point = ray.Point(t);
		distance = sqrt(pow(point[0] - ray.endpoint[0],2) + pow(point[1] - ray.endpoint[1],2) + pow(point[2] - ray.endpoint[2],2));
		cout << "single contact distance = " << distance << endl;
		hit.dist = t;
		hit.object = new Sphere(center,radius); 
	}
	else
	{
		double tmin = ((-1 * dot(ray.direction,eMinC) / dot(ray.direction,ray.direction)) - (sqrt(discriminant)) / (dot(ray.direction,ray.direction)));
		double tplus = ((-1 * dot(ray.direction,eMinC) / dot(ray.direction,ray.direction)) + (sqrt(discriminant)) / (dot(ray.direction,ray.direction)));
	
		t = ((-1 * dot(ray.direction,eMinC) / dot(ray.direction,ray.direction)) - (sqrt(discriminant)) / (dot(ray.direction,ray.direction)));
		cout << "double contact min = " << tmin << endl;
		hit.part = part;
		vec3 pointmin = ray.Point(tmin);
		vec3 pointplus = ray.Point(tplus);
		double distancemin = sqrt(pow(pointmin[0] - ray.endpoint[0],2) + pow(pointmin[1] - ray.endpoint[1],2) + pow(pointmin[2] - ray.endpoint[2],2));
		double distanceplus = sqrt(pow(pointplus[0] - ray.endpoint[0],2) + pow(pointplus[1] - ray.endpoint[1],2) + pow(pointplus[2] - ray.endpoint[2],2));
		if (distancemin < distanceplus)
		{
			hit.dist = tmin;
		}
		else
		{
			hit.dist = tplus;
		}
		cout << "double distancemin = " << distancemin << endl;
		cout << "double distanceplus = " << distanceplus << endl;
	}
	
	cout << "end sphere intersection" << endl;
    return hit;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
	cout << "sphere normal" << endl;
    vec3 normal;
	cout << "start sphere normal" << endl;
    //TODO; // compute the normal direction
	normal = (point - center);
    normal[0] *= 2;
	normal[1] *= 2;
	normal[2] *= 2;
	normal.normalized();
	return normal;
	cout << "end sphere normal" << endl;
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
