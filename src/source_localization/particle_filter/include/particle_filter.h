#ifndef PARTICLE_FILTER_H
#define PARTICLE_FILTER__H

#include "vector"

struct particle{
    //Fraction of the probability distribution
    double weight;
    //Concentration produced by the particle at some downwind test point
    double downwind_concentation;
    //The state which we are trying to predict is the combination of position and rate
    double position[3];
    double rate;
};
struct particle_set{
    std::vector<particle> particles;
};
struct state_space{
    // Default constructor
    state_space():x{0.0, 0.0}, y{0.0, 0.0}, z{0.0, 0.0}, rate{0.0, 0.0} {};

    state_space(double x_min, double x_max, double y_min, double y_max, double z_min, double z_max, double rate_min, double rate_max)
        :x{x_min, x_max}, y{y_min, y_max}, z{z_min, z_max}, rate{rate_min, rate_max}
        {};

    double x[2];
    double y[2];
    double z[2];
    double rate[2];
};
struct wind_model{
    // Default constructor
    wind_model(): sy{0, 0, 0}, sz{0, 0, 0} {};

    wind_model(double sya, double syb, double syc, double sza, double szb, double szc)
        :sy{sya,syb,syc},sz{sza,szb,szc}
        {};

    double sy[3];
    double sz[3];
};
struct measurement
{
    // Default constructor
    measurement(): az{0}, vel{0}, conc{0}, time_stamp{0} {};

    measurement(double azimuth, double velocity, double concentration, int time_stamp)
        : az{azimuth}, vel{velocity}, conc{concentration}, time_stamp{time_stamp}
        {};

    double location[3];
    double az;
    double vel;
    double conc;
    int time_stamp;
};


class ParticleFilter{
    ParticleFilter();
    ParticleFilter(int, state_space, wind_model);

    ~ParticleFilter();

    void initialize(int, state_space, wind_model); //For filter that is not constructed with params
    void initialize(); //For filter that has been constructed with params
    void predict();
    void reweight();
    void resample();

    particle_set ps;
    state_space ss_;
    wind_model wm_;
    
public:
    void updateFilter(measurement); //Execute predict,reweight,resample
    void getFilter();
    void printStatistics();
    
    
};

#endif