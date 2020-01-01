
#include "ray.hpp" 


Ray::Ray()
{
	m_pos = vec3f(0); 
	m_dir = vec3f(0);  
}

Ray::Ray(const Ray& t)
{
	m_pos = t.m_pos; 
	m_dir = t.m_dir;
}

Ray::Ray(const vec3f& p, const vec3f& d)
{
	m_pos = p; 
	m_dir = normal(d); 
}

Ray& Ray::operator=(const Ray& t)
{
	m_pos = t.m_pos; 
	m_dir = t.m_dir; 
	return *this; 
} 


