#ifndef UTILS_H
#define UTILS_H

#include "vector"

//3D position
struct position
{
    double pos[3];
};


// Each state represents a potential emission source in 3D (x,y,z) space emitting at a rate q
struct state
{
    // Global 3D position and emission rate (x,y,z,q)
    double s[4];
};

struct particle
{
    state p;
    double weight;
};

struct set
{
    int particle_count;
    std::vector<particle> particles;
};

struct filter_state
{
    int current_set;
    int counter;
    set sets[2];
};

struct transformation
{
    double xyz_yaw[4];
};

struct state_space
{
    double x[2];
    double y[2];
    double z[2];
    double rate[2];
};


namespace sl{
//Return transform of test point into source local (source being the particle) frame
position transform(const position& source, const position& test_point, const transformation& tf);

// Return a 
std::vector<double> uniform_dist(int count);

}


#endif