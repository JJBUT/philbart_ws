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

void SLAnemometer::ROSCallback()
{

}

bool SLAnemometer::SetRawData()
{

}

bool SLAnemometer::ProcessRawData()
{
  
}

bool SLAnemometer::GetProcessedData()
{
  
}












// // Returns the hypotonuse of the x and y velocity readings as the net velocity
// void SLAnemometer::calculate_velocity()
// {
//   //velocity = hypot(std::get<0>(data.velocity_components),std::get<1>(data.velocity_components));
  
//   return;
// }

// // Returns the azimuth of the wind using atan2, returning values in rads between -pi and +pi
// void SLAnemometer::calculate_azimuth()
// {
//   //azimuth= atan2 (std::get<1>(data.velocity_components),std::get<0>(data.velocity_components));

//   return;
// }


}

