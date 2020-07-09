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

bool SLAnemometer::calculate_velocity(SLAnemometerData *data)
{
  return false;
}

bool SLAnemometer::calculate_azimuth(SLAnemometerData *data)
{
  return false;
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


}

