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

// The fixed bounds on the 4D state space
struct state_space
{
    state_space(double x_min, double x_max, double y_min, double y_max, double z_min, double z_max, double rate_min, double rate_max)
        :x{x_min, x_max}, y{y_min, y_max}, z{z_min, z_max}, rate{rate_min, rate_max}
        {};
    double x[2];
    double y[2];
    double z[2];
    double rate[2];
};

// Wind model per the Gaussian Plume model classifications
struct wind_model
{
    
    wind_model(double sya, double syb, double syc, double sza, double szb, double szc )
        :sy{sya,syb,syc},sz{sza,szb,szc}
        {

        };
    double sy[3];
    double sz[3];
    
};

// Wind velocity and azimuth plus gas concentration
struct measurement
{
    double az;
    double vel;
    double conc;
    int time_stamp;
};




namespace sl{
// Return a test point transformed into a source local (source being the particle of concern) frame
position transform(const position& source, const position& test_point, const double yaw);

// Return a 1D vector of uniform random numbers from 0 to 1
std::vector<double> uniform_dist(int count);

}


#endif