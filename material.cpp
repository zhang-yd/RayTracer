
#include "material.hpp" 


Material::Material()
{
	m_diffuse_rate = INIT_RATE; 
	m_specular_rate = INIT_RATE; 
	m_reflect_rate = INIT_RATE; 
	m_refract_rate = INIT_RATE; 
	m_color = vec3f(0); 
	m_refract_index = 1; 
	m_specular_exp = 1; 
}  

Material::Material(const float& diffuse, const float& specular, const float& reflect, const float& refract, 
		const vec3f& color, const float& refract_index, const float& specular_exp): 
		m_diffuse_rate(diffuse), m_specular_rate(specular), m_reflect_rate(reflect), m_refract_rate(refract), 
		m_color(color), m_refract_index(refract_index), m_specular_exp(specular_exp) 
{
	
}


Material& Material::operator=(const Material& t)
{
	m_diffuse_rate = t.m_diffuse_rate; 
	m_specular_rate = t.m_specular_rate; 
	m_reflect_rate = t.m_reflect_rate; 
	m_refract_rate = t.m_refract_rate; 
	m_color = t.m_color; 
	m_refract_index = t.m_refract_index; 
	m_specular_exp = t.m_specular_exp; 
	return *this; 
} 


