#include "initialize.h"

Initialize::Initialize(int np, state_space bounds): 
    num_particles{np}, 
    ss{bounds}
{
    is_allocated= allocate();
    is_filled= fill();
}


Initialize::~Initialize() {}


bool Initialize::allocate()
{
    filter.reset(new filter_state());

    filter->counter=0;
    filter->current_set=0;

    for (size_t i = 0; i < 2; i++)
    {
        filter->sets[i].particle_count = num_particles;
        filter->sets[i].particles.resize(num_particles);
    }
    
    return true;
}

bool Initialize::fill()
{
    for (size_t i = 0; i < filter->sets[0].particle_count; i++)
    {
        std::vector<double> rnv= sl::uniform_dist(4); // "random number vector"
        filter->sets[0].particles[i].p.s[0]=ss.x[0]+rnv[0]*(ss.x[1]-ss.x[0]);
        filter->sets[0].particles[i].p.s[1]=ss.y[0]+rnv[1]*(ss.y[1]-ss.y[0]);
        filter->sets[0].particles[i].p.s[2]=ss.z[0]+rnv[2]*(ss.z[1]-ss.z[0]);
        filter->sets[0].particles[i].p.s[3]=ss.rate[0]+rnv[3]*(ss.rate[1]-ss.rate[0]);
        filter->sets[0].particles[i].weight=1.0/filter->sets[0].particle_count;
    }
    
    return true;
}


std::unique_ptr<filter_state> Initialize::getFilter()
{
    if (is_allocated == true && is_filled == true)
    {
        return std::move(filter);  
    }else{
        return nullptr;
    }
    
}