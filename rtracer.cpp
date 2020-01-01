

#include "rtracer.hpp" 
#include "log.hpp"

#include <string> 
#include <vector> 


RTRacer::RTRacer(const SceneMgr* s, const Sampler* sp, const std::string& file, const int w, const int h)
{
	m_scn = const_cast<SceneMgr *>(s); 
	m_sampler = const_cast<Sampler *>(sp); 
	m_file_name = file; 
	m_width = w; 
	m_height = h; 
	save_mode = PPM; 
}

std::string RTRacer::get_file_name()
{
	std::string ret; 
	std::size_t found = m_file_name.find('.'); 
	if(found != std::string::npos)
	{
		return m_file_name; 
	}

	if(save_mode == RTRacer::SAVE_TYPE::PNG)
	{
		ret = m_file_name + ".png"; 
	}
	else if(save_mode == RTRacer::SAVE_TYPE::PPM)
	{
		ret = m_file_name + ".ppm"; 
	}
	else if(save_mode == RTRacer::SAVE_TYPE::TXT)
	{
		ret = m_file_name + ".txt"; 
	}
	return ret; 
}

void RTRacer::set_mode(const int mode)
{
	save_mode = mode; 
}

void RTRacer::save(const std::vector<vec3f>& p)
{
	if(save_mode == PNG)
	{
		save_png(m_width, m_height, p, m_file_name); 
	}
	else if(save_mode == PPM)
	{
		save_ppm(m_width, m_height, p, m_file_name); 
	}
	glog->info("save render result into ", m_file_name, " with (W:", m_width, ", H:", m_height, ")"); 
}

void RTRacer::render()
{
	std::vector<vec3f> pixels(m_width * m_height); 

	for(int i=0; i < m_height; ++i)
	{
		for(int j=0; j < m_width; ++j)
		{
			vec3f pixel = vec3f(0, 0, 0); 
			for(int k=0; k<m_sampler->get_size(); ++k)
			{
				float cur_y = m_sampler->get_sampler_x(k) + i; 
				float cur_x = m_sampler->get_sampler_y(k) + j; 

				Ray ray = m_scn->m_camera.get_ray(cur_x, cur_y);
				pixel +=  m_scn->tracer(ray, 0); 
			}
			pixels[j + i*m_width] = pixel * (1.0f / m_sampler->get_size()); 
		}
	}

	m_file_name = get_file_name(); 

	save(pixels); 
}

