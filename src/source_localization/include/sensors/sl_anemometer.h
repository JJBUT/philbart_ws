#include "iostream"
#include "tuple"
#include "../include/sensors/sl_sensor.h"

#ifndef SL_ANEMOMETER_H
#define SL_ANEMOMETER_H
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
    public: bool calculate_velocity(SLAnemometerData *data);

    // Calculate the azimuth of the wind
    public: bool calculate_azimuth(SLAnemometerData *data);
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
    private: std::tuple<double, double> velocity_components; //NOTE: make this into a pointer so that way there is just one memory address where the data is always updated?
    
    // Given the x and y components of the incoming twist message, 
    // set the private values of velocity_components
    public: bool set_velocity_components(double x_velocity, 
                                         double y_velocity);
};

}

#endif