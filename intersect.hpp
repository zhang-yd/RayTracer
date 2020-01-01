
#ifndef _INTERSECT_HEAD_ 
#define _INTERSECT_HEAD_ 

#include "global.hpp" 
#include "vector.hpp" 
#include "material.hpp"
#include "ray.hpp" 


// A intersection info container 
class Intersect
{
public:
	explicit Intersect(); 

	void update_hit(const float &d, const vec3f& h, const vec3f& in, const vec3f& n, const Material& m); 

public:
	bool m_intersect;
	float m_depth; 
	vec3f m_hit; 
	vec3f m_normal; 
	vec3f m_in_dir; 
	Material m_material; 
}; 


#endif // _INTERSECT_HEAD_ 
