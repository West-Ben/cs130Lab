#include <algorithm>
#include "hierarchy.h"

// Reorder the entries vector so that adjacent entries tend to be nearby.
// You may want to implement box.cpp first.
void Hierarchy::Reorder_Entries()
{
    if(!entries.size()) return;
    //TODO;
    int min;
    for (int i = 0; i < entries.size() - 1; i++)
    {
        min = i + 1;
	for (int j = i + 1; j < entries.size(); j++)
	{
		if (min == i)
		{}
		else if ((entries[min].box.lo - entries[i].box.lo).magnitude() >  (entries[j].box.lo - entries[i].box.lo).magnitude() )   
		{
			min = j;
		}
	} 
	Entry temp = entries[i+1];
	entries[i+1] = entries[min];
	entries[min] = temp;
    }
        
}

// Populate tree from entries.
void Hierarchy::Build_Tree()
{
    if(!entries.size()) return;
    //TODO;
	for (int i = 0; i < entries.size(); i++)
	{
		tree.push_back(entries[i].box);
	}
}

// Return a list of candidates (indices into the entries list) whose
// bounding boxes intersect the ray.
void Hierarchy::Intersection_Candidates(const Ray& ray, std::vector<int>& candidates) const
{
    TODO;

}
