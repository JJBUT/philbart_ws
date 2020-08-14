#include <nrg_sl_node.h>

#include <geometry_msgs/TransformStamped.h>

NRGSLNode::NRGSLNode()
: nh_(), 
  private_nh_("~"),
  tfListener_(tfBuffer_)
{
  pf_params _pfp;
  private_nh_.param( "number_of_particles", 
                     _pfp.np,
                     1000 );
  private_nh_.param( "minimum_number_of_particles",
                     _pfp.np_min,
                     500 );
  private_nh_.param( "measurement_noise", 
                     _pfp.R,
                     1.0 );
  private_nh_.param( "resampling_noise",
                     _pfp.Q,
                     0.1);
  ROS_INFO_STREAM_NAMED( "nrg_source_localization_node", 
                         "  np: "<< _pfp.np <<
                         "  np_min: "<< _pfp.np_min <<
                         "  measurement_noise: "<< _pfp.R << 
                         "  resampling_noise: "<< _pfp.Q );

  state_space _ss;
  private_nh_.getParam( "x_bounds",
                        _ss.x );
  private_nh_.getParam( "y_bounds", 
                        _ss.y );
  private_nh_.getParam( "z_bounds", 
                        _ss.z );
  private_nh_.getParam( "rate_bounds", 
                        _ss.rate );
  ROS_INFO_STREAM_NAMED( "nrg_source_localization_node", 
                         "  x_bounds: "<< _ss.x[0] <<" to "<< _ss.x[1]  <<
                         "  y_bounds: "<< _ss.y[0] <<" to "<< _ss.y[1]  <<
                         "  z_bounds: "<< _ss.z[0] <<" to "<< _ss.z[1]  <<
                         "  rate_bounds: "<<  _ss.rate[0] <<" to "<< _ss.rate[1] );

  wind_model _wm;
  private_nh_.getParam( "wind_model_horizontal_dispersion", 
                        _wm.sy );
  private_nh_.getParam( "wind_model_vertical_dispersion", 
                        _wm.sz );
  ROS_INFO_STREAM_NAMED( "nrg_source_localization_node", 
                         "  horizontal_dispersion: "<< _wm.sy[0] <<" "<< _wm.sy[1] <<" "<< _wm.sy[2] <<
                         "  vertical_dispersion:"<< _wm.sz[0] <<" "<< _wm.sz[1] <<" "<< _wm.sz[2] );

  filter_.initialize(_pfp, _ss, _wm);

  sub_wind.subscribe( nh_, 
                  "/anemometer_data", 
                  20 );
  sub_gas.subscribe( nh_, 
                  "/gas_sensor_data", 
                  20 );

  sync.reset(new Sync(MySyncPolicy(100), sub_wind, sub_gas));   
  sync->registerCallback(boost::bind(&NRGSLNode::callback, this, _1, _2));

  return;
}




void NRGSLNode::callback(const AnemometerMsgConstPtr &wind, const MG811MsgConstPtr &gas)
{
  //TODO turn anemometer msg into twist stamped
  ros::Time _current_time = wind->header.stamp;

  geometry_msgs::TransformStamped _measurement_tf = tfBuffer_.lookupTransform( "base_link", 
                                                                               "map",
                                                                               _current_time);

  std::vector<double> _measurement_location = { _measurement_tf.transform.translation.x,
                                                _measurement_tf.transform.translation.y,
                                                _measurement_tf.transform.translation.z };
                                        
  measurement _m = { wind->azimuth, 
                     wind->speed, 
                     gas->concentration, 
                     static_cast<int>(_current_time.sec),
                     _measurement_location };

  filter_.updateFilter(_m);
} 


////////////////Entry Point/////////////////
int main(int argc, char** argv)
{
  //TODO put pf in namespace
  ROS_INFO_STREAM_NAMED("nrg_source_localization_node", "Starting source localization node");
  ros::init(argc, argv, "nrg_source_localization_node");
  NRGSLNode synchronizer;

  ros::spin();
  
  return(0);
}