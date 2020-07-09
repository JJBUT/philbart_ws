#include "iostream"
#include "string"

#ifndef SL_SENSOR_H
#define SL_SENSOR_H

//SLSensor should include:
    // name
    // frame

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

    public: double time_stamp;

    // Frame
     
    // Description

};

}



#endif 