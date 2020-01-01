
#ifndef _RAY_HEAD_ 
#define _RAY_HEAD_ 

#include "vector.hpp" 

class Ray
{
public:
	Ray(); 
	Ray(const Ray& t); 
	Ray(const vec3f& p, const vec3f& d); 

	Ray& operator=(const Ray& t); 

	friend std::ostream& operator<<(std::ostream& os, const Ray& t)
	{
		return os << "ray(" << t.m_pos << "," << t.m_dir; 
	}

public:
	vec3f m_pos; 
	vec3f m_dir; 
}; 


#endif // _RAY_HEAD_ 



