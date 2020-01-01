
#include "object.hpp" 

#include <cmath> 


void Sphere::intersect(Intersect& ites, const Ray& r) const
{
	vec3f L = m_pos - r.m_pos; 
	float r_len = dot(r.m_dir, L); 
	float l_len2 = dot(L, L); 
	float rl_dist2 = l_len2 - r_len * r_len; 

	if( l_len2 > m_radius * m_radius && 
		(rl_dist2 > m_radius * m_radius))
	{
		return; 
	} 

	float r_dist = 0; 
	if(l_len2 > m_radius*m_radius)
	{
		r_dist = r_len - sqrtf(m_radius*m_radius - rl_dist2); 
	}
	else
	{
		r_dist = r_len + sqrtf(m_radius * m_radius - rl_dist2); 
	} 

	// for too close object, avoid float error 
	if(r_dist < POSITIVE_FLOAT_ZERO)
	{
		return; 
	} 
	if(!ites.m_intersect || ites.m_depth > r_dist)
	{
		vec3f hit_point = r.m_pos + r.m_dir * r_dist; 
		vec3f in = normal(hit_point - m_pos); 
		ites.update_hit(r_dist, hit_point, r.m_dir, in, m_material); 
	}
} 



void Cube::intersect(Intersect& ites, const Ray& r) const
{
	// todo 
}



