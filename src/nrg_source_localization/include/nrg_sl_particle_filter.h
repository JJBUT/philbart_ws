#ifndef NRG_SL_PARTICLE_FILTER_H
#define NRG_SL_PARTICLE_FILTER_H

#include "vector"

struct pf_params{
    int np; 
    double Neff_lim;
    //Measurement noise
    double R;
    //Resampling lubricant
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
    std::vector<particle> particles;
    int np;

    double Neff_lim;
    // Measurement noise
    double R;
    // Resampling noise
    double Q;
};

struct state_space{
    /**
    * @brief Construct default zero paramaterized state space
    * @return Zero intialized state_space 
    */
    state_space():x{0.0, 0.0}, y{0.0, 0.0}, z{0.0, 0.0}, rate{0.0, 0.0} {};

    /**
    * @brief Construct input initialized state space
    * @param x_min The x-dimension lower bound (m)
    * @param x_max The x-dimension upper bound (m)
    * @param y_min The y-dimension lower bound (m)
    * @param y_max The y-dimension upper bound (m)
    * @param z_min The z-dimension lower bound (m)
    * @param z_max The z-dimension upper bound (m)
    * @param rate_min The rate lower bound (?)
    * @param rate_max The rate upper bound (?)
    * @return Input initialized state_space
    */
    state_space(double x_min, double x_max, double y_min, double y_max, double z_min, double z_max, double rate_min, double rate_max)
        :x{x_min, x_max}, y{y_min, y_max}, z{z_min, z_max}, rate{rate_min, rate_max}
        {};

    double x[2];
    double y[2];
    double z[2];
    double rate[2];
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
    bool ifNeff() const;

    
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
    * @param int The number of particlces 
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
    void initialize(int, state_space, wind_model); //TODO Change Neff and R to params 

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

//utils
namespace pf{
    /**
    * @brief Generate a vector of uniformly distributed random numbers from 0 to 1
    * @param int How many independent random numbers you want 
    * @return std::vector<double> A vector of length int holding unique uniformly distributed random numbers from 0 to 1 
    */
    std::vector<double> uniform_rn(int);
    
    /**
    * @brief Generate a single uniformly distributed random number from 0 to 1
    * @return double A single uniformly distributed random number from 0 to 1
    */
    double uniform_rn();
    
    /**
    * @note The global origin is always referenced at ( 0,0,0 )
    * @note The global zero azimuth is to the east (positive global x-axis)
    * 
    * @brief Transform a test point into the source local frame
    * @param double* The source local test point which will be generated
    * @param const double* The global test point, most often the location of a measurement
    * @param const double* The global source point, most often the location of a particle
    * @param const double& The rotation, most often the azimuth of the wind
    * @return 
    */
    void transform(double*, const double*, const double*, const double&);
    
    /**
    * @brief Generate a value from a gaussian distribution
    * @param double The test point
    * @param double The mean of the distribution
    * @param double The standard deviation of the distribution
    * @return double g(x) the value of the gaussian at the test point
    */
    double gaussian(double, double, double);
} //END of pf namespace

#endif