
#ifndef _CAMERA_HEAD_ 
#define _CAMERA_HEAD_ 


#include "ray.hpp" 
#include "vector.hpp" 

#include <string> 

class PerspectiveCamera
{
public:
	PerspectiveCamera(); 
	
	PerspectiveCamera(const float& fc, const float& w, const float& h, 
	 const vec3f& p, const vec3f& d, const vec3f& u); 

	Ray get_ray(const float& x, const float& y) const; 


public:
	float fov; 
	float m_width; 
	float m_height; 
	vec3f m_pos; 
	vec3f m_dir; 
	vec3f m_up; 

private:
	float focal; 
	vec3f x_comp; 
	vec3f y_comp; 
}; 


#endif // _CAMERA_HEAD_
