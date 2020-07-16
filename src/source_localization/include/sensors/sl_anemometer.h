#ifndef SL_ANEMOMETER_H
#define SL_ANEMOMETER_H


#include "tuple"
#include "../include/sensors/sl_sensor.h"

//put data struct here

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
    public: void calculate_velocity();

    // Calculate the azimuth of the wind
    public: void calculate_azimuth();
};


}

#endif