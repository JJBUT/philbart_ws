#ifndef SL_SENSOR_H
#define SL_SENSOR_H

#include "iostream"
#include "string"

namespace sl
{

class SLSensor
{
    public: SLSensor(); 
    public: ~SLSensor(); 

    public: std::string frame;

};

class SLSensorData
{
    public: SLSensorData();
    public: ~SLSensorData();

    private: double time_stamp;

    public: void set_time_stamp(double time_stamp);
};

}

#endif 