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

bool SLAnemometer::ProcessRawData(raw_anemometer_data& data)
{
  processed_anemometer_data working_pad;

  working_pad.azimuth= atan2 (data.y_velocity, data.x_velocity);
  working_pad.velocity= hypot(data.x_velocity, data.y_velocity);
  working_pad.frame= data.frame;
  working_pad.time_stamp= data.time_stamp;

  pad= working_pad;
  
  return true;
}

processed_anemometer_data SLAnemometer::GetProcessedData()
{
  return pad;
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

