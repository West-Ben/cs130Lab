#include <limits>
#include "box.h"

// Return whether the ray intersects this box.
bool Box::Intersection(const Ray& ray) const
{
    //TODO;
    float thix = (hi[0] - ray.endpoint[0]) / ray.direction[0];
    float tlox = (lo[0] - ray.endpoint[0]) / ray.direction[0];
    float thiy = (hi[1] - ray.endpoint[1]) / ray.direction[0];
    float tloy = (lo[1] - ray.endpoint[1]) / ray.direction[0];
    float thiz = (hi[2] - ray.endpoint[2]) / ray.direction[0];
    float tloz = (lo[2] - ray.endpoint[2]) / ray.direction[0];
 
    if (tlox > thix) swap(thix, tlox);

    if (tloy > thiy) swap(thiy, tloy);

    float tmin = (thix > thiy) ? thix : thiy;
    float tmax = (tlox < tloy) ? tlox : tloy;
    
    if (thix > tloy || thiy > tlox || tmin > tloz || tmax < thiz)
    {
	return false;
    }
 
    return true;
}

// Compute the smallest box that contains both *this and bb.
Box Box::Union(const Box& bb) const
{
    Box box;
    //TODO;
    vec3 lotohi = (this->lo - bb.hi);
    vec3 hitolo = (this->hi - bb.lo);
    if (lotohi.magnitude() > hitolo.magnitude())
    {
	box.hi = bb.hi;
	box.lo = this->lo;
    }
    else
    {
	box.hi = this->hi;
	box.lo = bb.lo;
    }
    return box;
}

// Enlarge this box (if necessary) so that pt also lies inside it.
void Box::Include_Point(const vec3& pt)
{
    //TODO;
    vec3 HtP = (pt - hi);
    vec3 LtP = (pt - lo);
    Ray r;
    
    if (HtP.magnitude() < LtP.magnitude())
    {
	r.endpoint = hi;
	r.direction = (hi - lo);
	hi = r.Point(r.direction.magnitude() + HtP.magnitude());
    }
    else
    {
	r.endpoint = lo;
	r.direction = (lo - hi);
	lo = r.Point(r.direction.magnitude() + LtP.magnitude());
    }
}

// Create a box to which points can be correctly added using Include_Point.
void Box::Make_Empty()
{
    lo.fill(std::numeric_limits<double>::infinity());
    hi=-lo;
}
