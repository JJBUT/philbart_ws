#include "iostream"
#include "math.h"

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
  velocity = hypot(std::get<0>(data.velocity_components),std::get<1>(data.velocity_components));
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

