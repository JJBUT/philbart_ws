#include "initialize.h"

Initialize::Initialize(int np, state_space bounds)
{
    num_particles = np;
    ss= bounds;

    bool is_allocated = allocate();
    bool is_filled = fill();
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
        filter->sets[i].particles.reserve(num_particles);
    }
    
    return true;
}

bool Initialize::fill()
{
    
    return true;
}


std::unique_ptr<filter_state> Initialize::GetFilter()
{
    if (is_allocated == true && is_filled == true)
    {
        return std::move(filter);  
    }else{
        return nullptr;
    }
    
}