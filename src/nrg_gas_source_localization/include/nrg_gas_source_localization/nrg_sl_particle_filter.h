#ifndef NRG_SL_PARTICLE_FILTER_H
#define NRG_SL_PARTICLE_FILTER_H

#include "vector"

struct pf_params{
    int np; 
    int np_min;
    //Measurement noise
    double R;
    //Resampling noise
    double Q;
};

/**
* @note The state we are predicting is the location and emission rate of a fugitive gas emission source (x,y,z,q)
*
* @brief Each particle represents a weighted state hypothesis 
* @param double downwind_conc The concentration produced at some location by the source represented by the particle 
* @param double position[3] The global location of the source
* @param double rate The emission rate of the source 
*/
struct particle{
    //Fraction of the probability distribution
    double weight;
    //Concentration produced by the particle at some downwind test point
    double downwind_conc;
    //The state which we are trying to predict is the combination of position and rate
    double position[3];
    double rate;
};

/**
* @brief The state and statistical characterization of the filter
* @param std::vector<particle> particles The particle set the filter use to represent the probability distribution of the state
* @param int np The number of particles 
* @param double R The measurement model noise
* @param double Q The resampling noise introduced to prevent single particle state collapse when resampling
*/
struct particle_set{
    std::vector<particle> particles; //TODO think about typedef
};

struct state_space{
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> z;
    std::vector<double>rate;
};

struct wind_model{
    /**
    * @brief Construct default zero paramaterized wind model
    * @param sy Horizontal dispersion parameters ()
    * @param sz Vertical dispersion parameters ()
    * @return Zero initialized wind_model
    */
    wind_model(): sy{0, 0, 0}, sz{0, 0, 0} {};

    /**
    * @brief Construct input initialized wind model
    * @param sy Horizontal dispersion parameters ()
    * @param sz Vertical dispersion parameters ()
    * @return Input initialized wind_model
    */
    wind_model(double sya, double syb, double syc, double sza, double szb, double szc)
        :sy{sya,syb,syc},sz{sza,szb,szc}
        {};

    double sy[3];
    double sz[3];
};

struct measurement
{
    /**
    * @brief Construct default zero paramaterized measurement
    * @param az Azimuth of wind velocity (rad)
    * @param vel Wind velocity (m/s)
    * @param conc Gas concentration (?)
    * @param time_stamp Measurement time (s)
    * @param location XYZ location of measurement (m, m, m)
    * @return Zero intialized measurement
    */
    measurement(): az{0}, vel{0}, conc{0}, time_stamp{0} {};

    /**
    * @brief Construct input initialized measurement
    * @param az Azimuth of wind velocity (rad)
    * @param vel Wind velocity (m/s)
    * @param conc Gas concentration (?)
    * @param time_stamp Measurement time (s)
    * @param location XYZ location of measurement (m, m, m)
    * @return Input initialized measurement
    */
    measurement(double azimuth, double velocity, double concentration, int time_stamp)
        : az{azimuth}, vel{velocity}, conc{concentration}, time_stamp{time_stamp}
        {};

    double az;
    double vel;
    double conc;
    int time_stamp;
    double location[3];
};

class ParticleFilter{
    /**
    * @brief Initialize an already paramaterized filter's particle set
    * @param int The number of particles to generate
    * @return void
    */
    void initialize(); // Change Neff and R to params

    /**
    * @brief Predict the concentration at the measurement location from each particle
    * @param measurement 
    * @return void
    */
    void predict(measurement);  

    /**
    * @brief Update the filter's particle set weights
    * @param measurement 
    * @return void
    */
    void reweight(measurement); 

    /**
    * @brief If Neff<Neff_lim then resample to prevent degeneracy
    * @return void
    */
    void resample(); 

    /**
    * @brief Check if the particle set is degenerate
    * @return bool True if the particle set is degenerate and Neff< Neff_lim
    */
    bool isDegenerate() const; //TODO make name more descriptive about return condition

    
    pf_params pfp_;
    state_space ss_;
    wind_model wm_;

    bool initialized;
    particle_set ps;
    
public:
    /**
    * @brief Construct an unparameterized filter
    * @return ParticleFilter
    */
    ParticleFilter(); 
    
    /**
    * @brief Construct a parameterized filter
    * @param pf_params Particle filter parameterization
    * @param state_space The state space bounds
    * @param wind_model The wind model parameters
    * @return ParticleFilter 
    */
    ParticleFilter(pf_params, state_space, wind_model); 
    
    /**
    * @brief Initialize an unparameterized filter
    * @param int The number of particles to generates
    * @param state_space The filter's state space
    * @param wind_model The filter's gaussian plume wind model dispersion parameters
    * @return void
    */
    void initialize(pf_params, state_space, wind_model);

    /**
    * @brief Call predict, reweight, and resample to process a measuremnt and update the filter
    * @param measurement A new measuremnt 
    * @return void
    
    */
    void updateFilter(measurement); 

    /**
    * @brief Print the filter's particle set mean
    * @return void
    */
    void printStatistics() const;
};

#endif