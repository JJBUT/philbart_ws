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

// A single weighted sample
struct particle
{
    state p;
    double weight;
};
// Structured grouping of particles
struct set
{
    int particle_count;
    std::vector<particle> particles;
};

// Primary particle filter structure
struct filter_state
{
    int current_set;
    int counter;
    set sets[2];
};

// Linear offset and 2D rotational yaw
struct transformation
{
    double xyz_yaw[4];
};

// The fixed bounds on the 4D state space
struct state_space
{
    double x[2];
    double y[2];
    double z[2];
    double rate[2];
};

// Wind model per the Gaussian Plume model classifications
struct wind_model
{
    double sy[3];
    double sz[3];
};

// Wind velocity and azimuth plus gas concentration
struct measurement
{
    double az;
    double vel;
    double conc;
};




namespace sl{
// Return a test point transformed into a source local (source being the particle of concern) frame
position transform(const position& source, const position& test_point, const transformation& tf);

// Return a 1D vector of uniform random numbers from 0 to 1
std::vector<double> uniform_dist(int count);

}


#endif