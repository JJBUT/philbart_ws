#ifndef NRG_SL_UTILS_H
#define NRG_SL_UTILS_H

#include <vector>
#include <string>

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

    std::vector< std::vector<double> > read_data( std::string );
} //END of pf namespace

#endif