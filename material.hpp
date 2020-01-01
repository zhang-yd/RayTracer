
#ifndef _MATERIAL_HEAD_ 
#define _MATERIAL_HEAD_ 

#include "vector.hpp"


class Material
{
public:
	Material(); 
	Material(const float& diffuse, const float& specular, const float& reflect, const float& refract, 
			const vec3f& color, const float& refract_index, const float& specular_exp); 

	Material& operator=(const Material& t); 

public:

	float m_diffuse_rate; 
	float m_specular_rate; 
	float m_reflect_rate; 
	float m_refract_rate; 
	vec3f m_color; 
	float m_refract_index; 
	float m_specular_exp; 
}; 



#endif // _MATERIAL_HEAD_ 
