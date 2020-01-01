
#ifndef _UTIL_HEAD_ 
#define _UTIL_HEAD_ 

#include "vector.hpp"

// #include <iostream> 
// #include <string>
#include <vector> 
#include <cmath>
#include <limits>

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cassert>
#include <cstring> 


template <typename T>
Vector3<T> 
reflect(const Vector3<T>& in, const Vector3<T>& n)
{
    Vector3<T> r = in - (n * 2.0f * dot(in, n)); 
    return r; 
}


template <typename T>
Vector3<T>
refract(const Vector3<T>& in, const Vector3<T>& n, const float rate_t, const float rate_i=1.0f)
{
    float cosi = - std::max(-1.0f, std::min(1.0f, dot(in, n))); 
    if(cosi < 0){
        return refract(in, -n, rate_i, rate_t); 
    }
    float eta = rate_i / rate_t; 
    float k = 1 - eta * eta * (1.0f - cosi * cosi); 
    return k < 0? Vector3<T>(1, 0, 0): in * eta + n * (eta * cosi - sqrtf(k));  
}

bool save_ppm(int width, int heigth, const std::vector<vec3f>& pixels, const std::string &file_name); 

bool save_png(int width, int heigth, const std::vector<vec3f>& pixels, const std::string &file_name); 

bool save_txt(int width, int height, const std::vector<vec3f>& pixels, const std::string &file_name); 


#endif // _UTIL_HEAD_
