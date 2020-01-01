
#include "light.hpp"

#include <iostream> 
#include <algorithm>


vec3f DirectionLight::get_diffuse(const vec3f& hit, const vec3f& n, const std::vector<Object *>& objs) const 
{
	float cross_angle = dot(n, m_dir); 
	return m_intensity * std::max(0.0f, cross_angle);  
}

vec3f DirectionLight::get_specular(const vec3f& hit, const vec3f& n, const vec3f& in_dir,const std::vector<Object *>& objs, const float& exp) const 
{
	return vec3f(0, 0, 0);  
}



vec3f SpotLight::get_diffuse(const vec3f& hit, const vec3f& n, const std::vector<Object *>& objs) const 
{
	vec3f ldir = normal(m_pos - hit); 
	float cross_angle = dot(ldir, n); 
	return m_intensity * std::max(0.0f, cross_angle); 
}

vec3f SpotLight::get_specular(const vec3f& hit, const vec3f& n, const vec3f& in_dir,const std::vector<Object *>& objs, const float& exp) const 
{
	vec3f ldir = normal(m_pos - hit);  
	return m_intensity * powf(std::max(0.0f, dot(-reflect(-ldir, n), in_dir)), exp); 
}

