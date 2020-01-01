
#include "sampler.hpp" 
#include "log.hpp" 

Sampler::Sampler(const int& s):size(s), generator_(time(0)), distribu_(0.0,1.0) 
{
    dx.clear(); 
    dy.clear(); 
    for(size_t i=0; i<s; ++i)
    {
        float tmp = static_cast<float>(distribu_(generator_)); 
        dx.push_back((tmp - 1.0)/2.0); 
        dy.push_back(tmp / 2.0); 
    }
    
    glog->info("sampler: ", size);
}

int Sampler::get_size()
{
    return size; 
}

float Sampler::get_sampler_x(const int& idx)
{
    return dx[idx]; 
}

float Sampler::get_sampler_y(const int& idy)
{
    return dy[idy]; 
}

