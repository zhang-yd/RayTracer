
#ifndef _RTRACER_HEAD_ 
#define _RTRACER_HEAD_ 


#include "scene.hpp"  
#include "util.hpp" 
#include "sampler.hpp"

#include <string> 

class RTRacer
{
public:
	enum SAVE_TYPE{
		PNG = 1, 
		PPM, 
		TXT  
	}; 

public:
	RTRacer(const SceneMgr* s, const Sampler* sp, const std::string &file, const int w, const int h); 

	void render(); 
	void set_mode(const int mode); 

private:
	std::string get_file_name(); 
	void save(const std::vector<vec3f>& p); 

private:
	std::string m_file_name; 
	int m_width; 
	int m_height; 
	int save_mode; 
	SceneMgr* m_scn; 
	Sampler* m_sampler; 
}; 


#endif // _RTRACER_HEAD_ 
