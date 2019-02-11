#include "mesh.h"
#include <fstream>
#include <string>
#include <limits>

// Consider a triangle to intersect a ray if the ray intersects the plane of the
// triangle with barycentric weights in [-weight_tolerance, 1+weight_tolerance]
static const double weight_tolerance = 1e-4;

// Read in a mesh from an obj file.  Populates the bounding box and registers
// one part per triangle (by setting number_parts).
void Mesh::Read_Obj(const char* file)
{
    std::ifstream fin(file);
    if(!fin)
    {
        exit(EXIT_FAILURE);
    }
    std::string line;
    ivec3 e;
    vec3 v;
    box.Make_Empty();
    while(fin)
    {
        getline(fin,line);

        if(sscanf(line.c_str(), "v %lg %lg %lg", &v[0], &v[1], &v[2]) == 3)
        {
            vertices.push_back(v);
            box.Include_Point(v);
        }

        if(sscanf(line.c_str(), "f %d %d %d", &e[0], &e[1], &e[2]) == 3)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
        }
    }
    number_parts=triangles.size();
}

// Check for an intersection against the ray.  See the base class for details.
Hit Mesh::Intersection(const Ray& ray, int part) const
{
    //TODO;
    Hit hit;
    hit.object = NULL;
    hit.part = part;
    hit.dist = 0;

    if (Intersect_Triangle(ray,part,hit.dist))
    {
        hit.object = this;
    }

    return hit;
}

// Compute the normal direction for the triangle with index part.
vec3 Mesh::Normal(const vec3& point, int part) const
{
    assert(part>=0);
    //TODO;
    vec3 normal = cross((vertices[triangles[part][1]] -  vertices[triangles[part][0]] ),(vertices[triangles[part][2]] - vertices[triangles[part][0]]));
    return normal.normalized();

}

// This is a helper routine whose purpose is to simplify the implementation
// of the Intersection routine.  It should test for an intersection between
// the ray and the triangle with index tri.  If an intersection exists,
// record the distance and return true.  Otherwise, return false.
// This intersection should be computed by determining the intersection of
// the ray and the plane of the triangle.  From this, determine (1) where
// along the ray the intersection point occurs (dist) and (2) the barycentric
// coordinates within the triangle where the intersection occurs.  The
// triangle intersects the ray if dist>small_t and the barycentric weights are
// larger than -weight_tolerance.  The use of small_t avoid the self-shadowing
// bug, and the use of weight_tolerance prevents rays from passing in between
// two triangles.
bool Mesh::Intersect_Triangle(const Ray& ray, int tri, double& dist) const
{
    //TODO; 
    vec3 edge1, edge2, h, s, q;
    float a, f, u, v;
    edge1 = vertices[triangles[tri][1]] - vertices[triangles[tri][0]];     
    edge2 = vertices[triangles[tri][2]] - vertices[triangles[tri][0]]; 
    h = cross(ray.direction,edge2);
    a = dot(edge1,h);

    if (a > -weight_tol && a < weight_tol)
    {
	return false;
    }
    f = 1.0 / a;
    s = ray.endpoint - vertices[triangles[tri][0]];
    u = f * (dot(s,h));
    if (u < 0.0 || u > 1.0)
    {
	return false;
    }
    q = cross(s,edge1);
    v = f * dot(ray.direction,q);
    if (v < 0.0 || (u + v) > 1.0)
    {
	return false;
    } 

    float t = f * dot(edge2,q);
    if (t > weight_tol)
    {
	dist = t;
        return true;
    } 
   
    return false;
}

// Compute the bounding box.  Return the bounding box of only the triangle whose
// index is part.
Box Mesh::Bounding_Box(int part) const
{
    Box b;
    //TODO;
    Ray rCB;
    rCB.endpoint = vertices[triangles[part][0]]; 
    vec3 CB = (vertices[triangles[part][1]] - vertices[triangles[part][2]]); 
    rCB.direction = ((-1.0) * CB);

    b.lo =  vertices[triangles[part][1]]; 
    b.hi = rCB.Point(rCB.direction.magnitude());

    return b;
}
