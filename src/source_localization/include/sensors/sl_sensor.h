#include "iostream"
#include "string"

#ifndef SL_SENSOR_H
#define SL_SENSOR_H

namespace sl
{

class SLSensor
{
    public: SLSensor(); 

    //std::cout << "Constructing SLSensor" << std::endl
    public: ~SLSensor(); 

    //The sensor (i.e. gas/wind/lidar)
    public: bool is_gas_sensor = false;

    public: bool is_anemometer = false;    
};

class SLSensorData
{
    public: SLSensorData();
    public: ~SLSensorData();

    //Think about making this a pointer because we only need
    // one memory location to store each data streams time_stamp information
    public: double time_stamp; 

    // public: Frame
     
    // public: Description
};

}

#endif 