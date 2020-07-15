#include "../include/sensors/sl_sensor.h"

/* July 15 2020 Note
// Think about turning the set functions into something more driven by
// ROS functionality/callbacks
*/

namespace sl{

// Default constructor
SLSensor::SLSensor()
{
  return;
}

// Default destructor
SLSensor::~SLSensor()
{
}


SLSensorData::SLSensorData()
{
  return;
}

// Default destructor
SLSensorData::~SLSensorData()
{
}

void SLSensorData::set_time_stamp(double time)
{
  time_stamp= time;

  return;
}

}
