
#include "util.hpp" 
#include <iostream> 
#include <fstream> 
#include <iomanip>
#include <sstream> 
#include <vector> 
#include <string> 

#include "lodepng.hpp"

bool save_txt(int width, int height, const std::vector<vec3f>& pixels, const std::string &file_name)
{
	FILE *fp = fopen(file_name.c_str(), "w");
	for(int i=0; i<width; ++i)
	{
		for(int j=0; j<height; ++j)
		{
			fprintf(fp, "(%f %f %f)", pixels[i*height + j].x, pixels[i*height + j].y, pixels[i*height + j].z); 
		}
		fprintf(fp, "\n"); 
	}
	fclose(fp);

	return true; 
}



bool save_ppm(int width, int heigth, const std::vector<vec3f>& pixels, const std::string &file_name) 
{
	std::ofstream ofs; 
	ofs.open(file_name); 
	ofs << "P6\n" << width << " " << heigth << "\n255\n"; 
	for(size_t i=0; i<heigth * width; ++i)
	{ 
		ofs << (char)(std::max(0.f, std::min(255.0f, pixels[i].x))); 
		ofs << (char)(std::max(0.f, std::min(255.0f, pixels[i].y))); 
		ofs << (char)(std::max(0.f, std::min(255.0f, pixels[i].z))); 
	}
	ofs.close();
	return true; 
}


bool save_png(int width, int height, const std::vector<vec3f>& pixels,const std::string &file_name)
{
	std::vector<unsigned char> pixels_buffer; 
	for(size_t i=0; i<width * height; ++i)
	{
		pixels_buffer.push_back(int(pixels[i].x)); 
		pixels_buffer.push_back(int(pixels[i].y)); 
		pixels_buffer.push_back(int(pixels[i].z)); 
		pixels_buffer.push_back(255); 
	}
	unsigned error = lodepng::encode(file_name, pixels_buffer, width, height); 
	if(error != 0){
		return false; 
	}
	pixels_buffer.clear(); 
	return true; 
}


