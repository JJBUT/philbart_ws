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

    // Remove data from incoming sensor msg and place into custom struct
    private: virtual bool SetRawData()= 0;

    // Calculates derived values and sets processed data
    private: virtual bool ProcessRawData()= 0;  

};


}

#endif 