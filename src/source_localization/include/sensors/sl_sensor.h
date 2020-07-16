#ifndef SL_SENSOR_H
#define SL_SENSOR_H

#include "iostream"
#include "string"

namespace sl
{

class SLSensor
{
    // Interface class for sensors (i.e. contains only virtual functions)
    public: SLSensor(); 
    public: ~SLSensor(); 

    public: virtual void ROSCallback()= 0; // Pure virtual 

    private: virtual bool SetRawData()= 0;

    private: virtual bool ProcessRawData()= 0;

    public: virtual bool GetProcessedData()= 0;
};


}

#endif 