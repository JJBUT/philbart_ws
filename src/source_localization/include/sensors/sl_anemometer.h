#ifndef SL_ANEMOMETER_H
#define SL_ANEMOMETER_H


#include "tuple"
#include "../include/sensors/sl_sensor.h"


namespace sl{

// Forward declaration
class SLAnemometerData;

class SLAnemometer: public SLSensor
{
    public: SLAnemometer();
    public: ~SLAnemometer();

    // The magnitude of the wind velocity
    public: double velocity;

    // The azimuth of the wind velocity with respect to the "anemometer_link" frame
    public: double azimuth;

    // Calculate the magnitude of the velocity
    public: void calculate_velocity(SLAnemometerData& data);

    // Calculate the azimuth of the wind
    public: void calculate_azimuth(SLAnemometerData& data);
};

// SLAnemometer is a "sub-class" of SLSensorData
class SLAnemometerData: public SLSensorData
{
    //Constructor for class that stores anemometer data
    public: SLAnemometerData();

    //Destructor for class that stores anemometer data
    public: ~SLAnemometerData();

    // Components of the velocity read by the anemometer given in 
    // the "anemometer_link" frame
    public: std::tuple<double, double> velocity_components; 
    
    // Given the x and y components of the incoming twist message, 
    // set the private values of velocity_components
    public: void set_velocity_components(double x_velocity, 
                                         double y_velocity);
    

};

}

#endif