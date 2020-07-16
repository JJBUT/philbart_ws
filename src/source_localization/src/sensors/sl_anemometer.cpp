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

void SLAnemometer::ROSCallback(const geometry_msgs::TwistStamped& msg)
{
  rad.x_velocity= msg.twist.linear.x;
  rad.y_velocity= msg.twist.linear.y;
  rad.time_stamp= msg.header.stamp.sec;
  rad.frame= msg.header.frame_id;

  bool data_processed= ProcessRawData();

  return;  
}

bool SLAnemometer::ProcessRawData()
{
  processed_anemometer_data working_pad;

  working_pad.azimuth= atan2 (rad.y_velocity, rad.x_velocity);
  working_pad.velocity= hypot(rad.x_velocity, rad.y_velocity);
  working_pad.frame= rad.frame;
  working_pad.time_stamp= rad.time_stamp;

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

