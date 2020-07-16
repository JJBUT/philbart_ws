#ifndef SL_ANEMOMETER_H
#define SL_ANEMOMETER_H

// Standard
#include "tuple"

// ROS
#include "geometry_msgs/TwistStamped.h"

// Custom
#include "../include/sensors/sl_sensor.h"


typedef struct 
{
    double x_velocity;
    double y_velocity;
    double time_stamp;
    std::string frame;
} raw_anemometer_data;

typedef struct
{
    double velocity;
    double azimuth;
    double time_stamp;
    std::string frame;
} processed_anemometer_data;

namespace sl{

// Forward declaration
class SLAnemometerData;

class SLAnemometer: public SLSensor
{
    public: SLAnemometer();
    public: ~SLAnemometer();

    private: raw_anemometer_data rad;

    public: processed_anemometer_data pad;

    public: void ROSCallback(const geometry_msgs::TwistStamped& msg);

    private: bool SetRawData();

    private: bool ProcessRawData();

    public: processed_anemometer_data GetProcessedData();



};

}

#endif