

#include "camera.hpp" 
#include "log.hpp"

PerspectiveCamera::PerspectiveCamera()
{

}

PerspectiveCamera::PerspectiveCamera(const float& fv, const float& w, const float& h, 
	 const vec3f& p, const vec3f& d, const vec3f& u): fov(fv), m_width(w), 
	 m_height(h), m_pos(p), m_dir(d), m_up(u)
{
	y_comp = normal(m_up);    				// (0, 1, 0)
	x_comp = normal(cross(m_dir, m_up));    // (1, 0, 0) 
	focal = m_height * (1.0f * tan(fov / 2.0)); 

	glog->info("Camera::  x:", x_comp, "  y:", y_comp, "  focal:", focal); 
}


Ray PerspectiveCamera::get_ray(const float& x, const float& y) const
{
	Ray r; 
	r.m_pos = m_pos; 
	r.m_dir = normal(m_dir * focal + x_comp*(x - m_width/2.0) + y_comp*(-y + m_height/2.0)); 

	return r; 
}


