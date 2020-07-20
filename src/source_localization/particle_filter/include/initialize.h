#ifndef INITIALIZE_H
#define INITIAlIZE_H

//stl
#include "memory"

//custom
#include "utils.h"

class initialize
{
private:
    int num_particles;

    //State space dimensions specified by default or user input
    state_space ss;

    // Pointer to the memory where the filter will be for the entire duration of the filter
    std::unique_ptr<filter_state> filter;

    // Allocate the memory in filter
    bool allocate();
    
    //Populate the allocated memory with randomly seeded particles
    bool fill();

public:
    initialize(int np, state_space bounds);
    ~initialize();

    // You may return std::unique_ptr<T> to express that the function creates 
    // an object and immediately gives the ownership of it to the caller. Very typical for factory 
    // functions - they often return smart pointer to base type or vector of smart pointers.
    std::unique_ptr<filter_state> get_filter();
    // std::unique_ptr<int> get_uptr(){return std::move(uptr);};
};


#endif