#include "iostream"
#include "../include/sensors/sl_anemometer.h"

namespace sl{

// Default constructor
SLAnemometer::SLAnemometer()
{
  return;
}
//Default Destructor
SLAnemometer::~SLAnemometer()
{
}

void SLAnemometer::calculate_velocity(SLAnemometerData& data)
{
  return;
}

void SLAnemometer::calculate_azimuth(SLAnemometerData& data)
{
  return;
}

// Default constructor
SLAnemometerData::SLAnemometerData()
{
  return;
}
//Default Destructor
SLAnemometerData::~SLAnemometerData()
{
}

void SLAnemometerData::set_velocity_components(double x_velocity, double y_velocity)
{
  velocity_components= std::make_tuple (x_velocity, y_velocity);

  return;
}



}

