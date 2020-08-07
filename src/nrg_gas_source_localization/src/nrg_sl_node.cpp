#include <gmx200_anemometer/AnemometerMsg.h>

#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>

#include <boost/bind.hpp>

using namespace gmx200_anemometer;

void callback(const AnemometerMsg& msg_1, const AnemometerMsg& msg_2)
{
  // Solve all of perception here...
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "amcl");
  ros::NodeHandle nh;

  message_filters::Subscriber<AnemometerMsg> sub_1(nh, "chanell_1", 1);
  message_filters::Subscriber<AnemometerMsg> sub_2(nh, "channel_2", 1);
  message_filters::TimeSynchronizer<AnemometerMsg, AnemometerMsg> sync(sub_1, sub_2, 10);
  //sync.registerCallback(boost::bind(&callback, _1, _2));
  ros::spin();
  
  return(0);
}