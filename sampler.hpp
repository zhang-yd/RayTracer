
#ifndef _SAMPLER_HEAD_ 
#define _SAMPLER_HEAD_ 

#include <vector>
#include <ctime> 
#include <random> 
#include <iostream> 

#include "global.hpp"

class Sampler
{
public:
    Sampler(const int& s);  
    int get_size(); 
    float get_sampler_x(const int& idx); 
    float get_sampler_y(const int& idy); 
private:
    int size; 
    std::vector<float> dx; 
    std::vector<float> dy; 
    std::default_random_engine generator_; 
    std::uniform_real_distribution<double> distribu_; 
}; 


#endif // _SAMPLER_HEAD_ 
