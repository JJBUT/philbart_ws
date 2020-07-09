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

    //The frame of the sensor as specified in the tf tree
    public: bool is_anemometer = false;

        
};

//SLSensorData should include:
    // the sensor that generated the data 
    // time

class SLSensorData
{
    public: SLSensorData();
    public: ~SLSensorData();

    // Assign values to sensor like "data.sensor = &anemometer;"
    // where anemometer is "sl::SLSensor anemometer;"
    public: SLSensor* sensor; 

    public: double time_stamp;

};

}



#endif 