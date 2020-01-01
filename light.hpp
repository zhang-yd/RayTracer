
#ifndef _LIGHT_HEAD_ 
#define _LIGHT_HEAD_ 

#include "ray.hpp" 
#include "vector.hpp"
#include "object.hpp" 
#include "intersect.hpp" 
#include "util.hpp" 


// we define the Light Color in its intensity.  Intensity is the base attribution
class Light
{
public:
	Light(): m_intensity(vec3f(0)) {} 
	Light(const vec3f& its): m_intensity(its) {} 
	virtual ~Light() {}

	virtual vec3f get_diffuse(const vec3f& hit, const vec3f& n, const std::vector<Object *>& objs) const =0; 
	virtual vec3f get_specular(const vec3f& hit, const vec3f& n, const vec3f& in_dir,const std::vector<Object *>& objs, const float& exp) const = 0; 

protected:
	vec3f m_intensity; 
}; 



// Direction Light: contains intensity and direction 
class DirectionLight: public Light
{
public:
	DirectionLight():Light(), m_dir(vec3f(0)) {}
	DirectionLight(const vec3f& d, const vec3f& its): Light(its), m_dir(d) {}

	vec3f get_diffuse(const vec3f& hit, const vec3f& n, const std::vector<Object *>& objs) const override; 
	vec3f get_specular(const vec3f& hit, const vec3f& n, const vec3f& in_dir,const std::vector<Object *>& objs, const float& exp) const override;  

private:
	vec3f m_dir;  
}; 


// Spot Light: contains intensity and position 
class SpotLight: public Light
{
public:
	SpotLight():Light(), m_pos(vec3f(0)) {} 
	SpotLight(const vec3f& p, const vec3f& its): Light(its), m_pos(p) {}

	vec3f get_diffuse(const vec3f& hit, const vec3f& n, const std::vector<Object *>& objs) const override; 
	vec3f get_specular(const vec3f& hit, const vec3f& n, const vec3f& in_dir,const std::vector<Object *>& objs, const float& exp) const override;  

private:
	vec3f m_pos; 
}; 


#endif // _LIGHT_HEAD_ 
