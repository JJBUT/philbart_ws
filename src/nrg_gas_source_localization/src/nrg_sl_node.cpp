#include <nrg_sl_node.h>

#include <iostream>

NRGSLNode::NRGSLNode()
{
  pf_params _pfp;
  private_nh_.param("number_of_particles", _pfp.np, 1000);
  private_nh_.param("minimum_number_of_particles", _pfp.np_min, 500);
  private_nh_.param("measurement_noise", _pfp.R, 1.0);
  private_nh_.param("resampling_noise", _pfp.Q, 0.1);

  ROS_INFO_STREAM(_pfp.Q);

  state_space _ss;
  //private_nh_.param("x_bounds", _ss.x);

  wind_model _wm;

  filter_.initialize(_pfp, _ss, _wm );


  private_nh_.param("anemometer_topic", anemometer_topic_);
  private_nh_.param("gas_sensor_topic", gas_sensor_topic_);
  sub1.subscribe(nh_, "/in1", 10);
  sub2.subscribe(nh_, "/in2", 10);
  sync.reset(new Sync(MySyncPolicy(10), sub1, sub2));   
  sync->registerCallback(boost::bind(&NRGSLNode::callback, this, _1, _2));
}

void NRGSLNode::callback(const AnemometerMsgConstPtr &in1, const MG811MsgConstPtr &in2)
{
} 


int main(int argc, char** argv)
{
  ros::init(argc, argv, "nrg_sl_node");
  NRGSLNode synchronizer;

  ros::spin();
  
  return(0);
}