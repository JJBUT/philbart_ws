/*Author Jack Borer July 2020
//Build Command: catkin build source_localization --cmake-args -DCMAKE_BUILD_TYPE=Debug 
*/


//Standard library
#include "iostream"
#include "memory" //smart pointers

//roscpp
#include "ros/ros.h"

//Required ROS msgs
#include "std_msgs/String.h"
#include "nav_msgs/OccupancyGrid.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float32.h"


// Maybe once we import the header files this error will do away
// using namespace sl; 

//Pose hypothesis
static const std::string node_name_ = "sl";

static const std::string map_topic_ = "map";
static const std::string odom_topic_ = "odometry/filtered_map";
static const std::string anemometer_topic_ = "anemometer/data";
static const std::string gas_sensor_topic_ = "gas_sensor/data";

class SLNode
{
    public:
      SLNode();
      ~SLNode() {};

    private:  
      std::string base_frame_id_;
      std::string map_frame_id_; 

      ros::NodeHandle nh_;
      ros::Subscriber map_sub_;
      ros::Subscriber map_pose_sub_;
      ros::Subscriber anemometer_sub_;
      ros::Subscriber gas_sensor_sub_;

      //No update allowed, it's either receieved or not
      bool map_received_; 

      std::string transport_model_type_;

      void mapCB(const nav_msgs::OccupancyGrid& msg);
      void mapOdomCB(const nav_msgs::Odometry& msg);
      void anemometerCB(const geometry_msgs::Twist& msg);
      void gasSensorCB(const std_msgs::Float32& msg);
  
};

boost::shared_ptr<SLNode> sl_node_ptr;

int main(int argc, char** argv)
{
  ros::init(argc, argv, node_name_);
  ros::NodeHandle nh;

  sl_node_ptr.reset(new SLNode());
  

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
  // Think about using a private nodehandle for some reason?

  /*
  // Uncomment this module when the parameter server has been brought online
  //Future proofing the node for adding transport models later
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

  //Get and store static transforms
  map_sub_ = nh_.subscribe(map_topic_, 2, &SLNode::mapCB, this);
  map_pose_sub_ = nh_.subscribe(odom_topic_, 2, &SLNode::mapOdomCB, this);
  anemometer_sub_ = nh_.subscribe(anemometer_topic_, 2, &SLNode::anemometerCB, this);
  gas_sensor_sub_ = nh_.subscribe(gas_sensor_topic_, 2, &SLNode::gasSensorCB, this);

}

void SLNode::mapCB(const nav_msgs::OccupancyGrid& msg){}
void SLNode::mapOdomCB(const nav_msgs::Odometry& msg){}
void SLNode::anemometerCB(const geometry_msgs::Twist& msg){}
void SLNode::gasSensorCB(const std_msgs::Float32& msg){}

