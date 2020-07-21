#ifndef INITIALIZE_H
#define INITIAlIZE_H

//stl
#include "memory"

//custom
#include "utils.h"

class Initialize
{
private:
    bool is_allocated;
    bool is_filled;

    // Number of particles  to build the filter with, is a constant
    int num_particles;
    // State space dimensions specified by default or user input
    state_space ss;
    // Pointer to the memory where the filter will be for the entire duration of the filter
    std::unique_ptr<filter_state> filter;
    // Allocate the filter memory
    bool allocate();
    //Populate the allocated memory of the first set only with random uniformly seeded particles
    bool fill();

public:
    Initialize(int np, state_space bounds);
    ~Initialize();

    // You may return std::unique_ptr<T> to express that the function creates 
    // an object and immediately gives the ownership of it to the caller. Very typical for factory 
    // functions - they often return smart pointer to base type or vector of smart pointers.
    // Return unique pointer to the most critical filter infrastructure
    std::unique_ptr<filter_state> GetFilter();
   
};


#endif