
#ifndef _SCENE_HEAD_ 
#define _SCENE_HEAD_ 

#include "camera.hpp" 
#include "object.hpp" 
#include "vector.hpp"
#include "light.hpp"
#include "util.hpp"

#include <vector>


const vec3f WHITE_LIGHT = vec3f(255.0, 255.0, 255.0); 


class SceneMgr
{
public:
	SceneMgr(const vec3f& bg, const PerspectiveCamera& c);

	void add_object(const Object* ob); 
	void add_light(const Light* lg); 

	vec3f tracer(const Ray& r, const int depth);   

private:
	bool world_intersect(const Ray& r, Intersect& ites) const;  

	vec3f minor_correct(const vec3f& out, const vec3f& n, const vec3f& hit); 

public:
	vec3f m_bg; 
	PerspectiveCamera m_camera; 

	std::vector<Light *> m_lights; 
	std::vector<Object *> m_objects; 

	float width, height; 
}; 


#endif // _SCENE_HEAD_ 
