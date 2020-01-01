
#include "intersect.hpp" 


Intersect::Intersect()
{
	m_intersect = false; 
	m_depth = MAX_DISTANCE; 
	m_hit = vec3f(0); 
	m_normal = vec3f(0); 
	m_in_dir = vec3f(0); 
	m_material = Material();
}

void Intersect::update_hit(const float &d, const vec3f& h, const vec3f& in, const vec3f& n, const Material& m)
{
	m_intersect = true; 
	m_depth = d;
	m_normal = n; 
	m_hit = h; 
	m_in_dir = in; 
	m_material = m; 
}


