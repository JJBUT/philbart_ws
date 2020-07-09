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

SLNode::SLNode() {}

