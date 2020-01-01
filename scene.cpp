
#include "scene.hpp" 

#include <iostream> 


SceneMgr::SceneMgr(const vec3f& bg, const PerspectiveCamera& c)
{
	m_bg = bg; 
	m_camera = c; 
	m_lights.clear(); 
	m_objects.clear(); 
	height = m_camera.m_height; 
	width  = m_camera.m_width; 
}

void SceneMgr::add_object(const Object* ob)
{
	m_objects.push_back(const_cast<Object *>(ob)); 
}

void SceneMgr::add_light(const Light* lg)
{
	m_lights.push_back(const_cast<Light *>(lg)); 
}


bool SceneMgr::world_intersect(const Ray& r, Intersect& ites) const
{    
	for(size_t i=0; i<m_objects.size(); ++i)
	{
		m_objects[i]->intersect(ites, r); 
	}
    return true; 
}

vec3f SceneMgr::minor_correct(const vec3f& out, const vec3f& n, const vec3f& hit)
{
	if(dot(out, n) < 0)
	{
		return hit - n * SCENE_MINOR; 
	}
	return hit + n * SCENE_MINOR; 
} 


vec3f SceneMgr::tracer(const Ray& r, const int depth)
{

	if(depth > MAX_TRACER_DEPTH)
	{
		return m_bg; 
	}
	Intersect ites; 
	world_intersect(r, ites); 
	if(!ites.m_intersect)
	{
		return m_bg; 
	}

	vec3f reflect_dir = normal(reflect(r.m_dir, ites.m_normal)); 
	vec3f refract_dir = normal(refract(r.m_dir, ites.m_normal, ites.m_material.m_refract_index)); 

	vec3f reflect_orig = minor_correct(reflect_dir, ites.m_normal, ites.m_hit); 
	vec3f refract_orig = minor_correct(refract_dir, ites.m_normal, ites.m_hit); 

	vec3f reflect_color = tracer(Ray(reflect_orig, reflect_dir), depth + 1); 
	vec3f refract_color = tracer(Ray(refract_orig, refract_dir), depth + 1); 

	vec3f diffuse_color, specular_color;  
	for(size_t i=0; i<m_lights.size(); ++i)
	{
		diffuse_color += m_lights[i]->get_diffuse(ites.m_hit, ites.m_normal, m_objects); 
		specular_color += m_lights[i]->get_specular(ites.m_hit, ites.m_normal, r.m_dir, m_objects, ites.m_material.m_specular_exp); 
	}

	return multi(ites.m_material.m_color, diffuse_color) * ites.m_material.m_diffuse_rate + \
			multi(WHITE_LIGHT, specular_color) * ites.m_material.m_specular_rate + \
			reflect_color * ites.m_material.m_reflect_rate + \
			refract_color * ites.m_material.m_refract_rate; 
}

