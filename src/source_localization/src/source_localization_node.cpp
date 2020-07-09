/*Author Jack Borer*/

//Standard library
#include "iostream"
#include "memory" //smart pointers

//roscpp
#include "ros/ros.h"

//Required ROS msgs
#include "std_msgs/String.h"


// Maybe once we import the header files this error will do away
// using namespace sl; 

//Pose hypothesis
static const std::string node_name_ = "sl";
static const std::string anemometer_topic_ = "anemometer/data";
static const std::string gas_sensor_topic_ = "gas_sensor/data";
static const std::string pose_topic_ = "odometry/filtered_map";

class SLNode
{
    public:
      SLNode();
      ~SLNode();

    private:  
      std::string base_frame_id_;
      std::string map_frame_id_; 

      ros::subscriber map_sub_;
      ros::Subscriber map_pose_sub_;
      ros::Subscriber anemometer_sub_;
      ros::Subscriber gas_sensor_sub_;

      //No update allowed, it's either receieved or not
      bool map_received_; 

      std::string transport_model_type_;
  
};

boost::shared_ptr<SLNode> source_localization_node_ptr;

int main(int argc, char** argv)
{
  ros::init(argc, argv, node_name_);
  ros::NodeHandle nh;
  
  //Run using ROS, may add .bag file functionality later
  if (1)
  {
    ros::spin();
  }

  return(0);
}

SLNode::SLNode() 
{
  // Get all parameters off of the parameter server
  // Think about using a private nodehandle?
  /*
  // Uncomment this module when the parameter server has been brought online
  // This code is future proofing the node for future transport models
  std::string tmp_model_type;
  private_nh_.param("transport_model_type", tmp_model_type, std::string("gaussian_plume"));
  if(tmp_model_type == "gaussian_plume")
  {
    transport_model_type_ = "GAUSSIAN_PLUME";
  }else
  {
    ROS_WARN("Unknown transport model type \"%s\"; defaulting to gaussian_plume model", tmp_model_type.c_str());
    transport_model_type_ = "GAUSSIAN_PLUME";
  }
  */


}

