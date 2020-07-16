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

    public: virtual void ROSCallback();

    public: virtual bool SetRawData();

    public: virtual bool ProcessRawData();

    public: virtual bool GetProcessedData();
};


}

#endif 