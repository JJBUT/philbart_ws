/*Author Jack Borer July 2020
//Build Command: catkin build source_localization --cmake-args -DCMAKE_BUILD_TYPE=Debug 
*/

/*Big Picture Questions
// Do I need std::mutex functionality
// How do shared pointers interact with ros::spin?
*/

/* Workover of the alloc code
Files used: 
  -pf.cpp - main code
  -source_localization_node.cpp -default run and check returned values
  -pf.h - pf, sample, and sampl_set data structs

Implementation notes:
  -Turn the pf sample_sets back into a regular value, not  a pointer
  -Keep the sample sets samples a smart pointer
  -Have both set and sample temp objects be raw ptrs in pf.cpp alloc fn

Additional work:
 -Change pf_init_uniform to handle pf's new structure

*/

/*
// To watch smart pointer value  in debug: <smart_ptr_obj>._M_ptr
*/


//Standard library
#include "iostream"
#include "memory" //smart pointers

//roscpp
#include "ros/ros.h"

//Required ROS msgs and srvs
#include "std_msgs/String.h"
#include "nav_msgs/OccupancyGrid.h" // Can I remove this becasue it is decalred in map.h?
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/TwistStamped.h"
#include "std_msgs/Float32.h"
#include "nav_msgs/GetMap.h"

//Custom includes
#include "../include/map/map.h"
#include "../include/pf/pf.h"
#include "../include/data/data_structs.h"




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
      void handleMapMessage(const nav_msgs::OccupancyGrid& msg);
      void mapReceived(const nav_msgs::OccupancyGridConstPtr& msg);
      void requestMap();


      // Particle filter
      std::shared_ptr<pf_t> pf_;
      int min_particles_, max_particles_;
      bool pf_init_;

      // State space limits
      double z_min_;
      double z_max_;
      double rate_min_;
      double rate_max_;

      // Data
      int max_data_age_;
      anemometer_data ad_;
      // Odom
      // Gas sensor


      std::string base_frame_id_;
      std::string global_frame_id_; 

      std::shared_ptr<map_t> map_;

      bool use_map_topic_;
      bool first_map_only_;
      bool first_map_received_;
      bool map_received_; 

      std::string transport_model_type_;

      ros::NodeHandle nh_;
      ros::NodeHandle private_nh_;
      ros::Subscriber map_sub_;
      ros::Subscriber map_pose_sub_;
      ros::Subscriber anemometer_sub_;
      ros::Subscriber gas_sensor_sub_;
      
      void mapOdomCB(const nav_msgs::Odometry& msg);
      void anemometerCB(const geometry_msgs::TwistStamped& msg);
      void gasSensorCB(const std_msgs::Float32& msg);
  
};

std::unique_ptr<SLNode> sl_node_ptr;

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

SLNode::SLNode() :
        first_map_received_(false)
{
  // Get all parameters off of the parameter server
  // Think about using a private nodehandle for some reason?
  private_nh_.param("use_map_topic", use_map_topic_, true);
  private_nh_.param("base_frame_id", base_frame_id_, std::string("base_link"));
  private_nh_.param("global_frame_id", global_frame_id_, std::string("map"));
  private_nh_.param("min_particles", min_particles_, 100);
  private_nh_.param("max_particles", max_particles_, 5000);
  private_nh_.param("z_min", z_min_, 0.0);
  private_nh_.param("z_max", z_max_, 20.0);
  private_nh_.param("rate_min", rate_min_, 0.0);
  private_nh_.param("rate_max", max_data_age_, 5);
  std::string tmp_model_type;
  private_nh_.param("transport_model_type", tmp_model_type, std::string("gaussian_plume"));
  private_nh_.param("data_age_max", rate_max_, 20000.0);

  if(tmp_model_type == "gaussian_plume")
  {
    transport_model_type_ = "GAUSSIAN_PLUME";
  }else{
    ROS_WARN("Unknown transport model type \"%s\"; defaulting to gaussian_plume model", tmp_model_type.c_str());
    transport_model_type_ = "GAUSSIAN_PLUME";
  }
  
  if(use_map_topic_){ //line 490
    map_sub_ = nh_.subscribe(map_topic_, 1, &SLNode::mapReceived, this);
    ROS_INFO("Subscribed to map topic.");
  }else{
    requestMap();
  }

  map_pose_sub_ = nh_.subscribe(odom_topic_, 2, &SLNode::mapOdomCB, this);
  anemometer_sub_ = nh_.subscribe(anemometer_topic_, 2, &SLNode::anemometerCB, this);
  gas_sensor_sub_ = nh_.subscribe(gas_sensor_topic_, 2, &SLNode::gasSensorCB, this);

}

void 
SLNode::mapOdomCB(const nav_msgs::Odometry& msg)
{

}

void 
SLNode::anemometerCB(const geometry_msgs::TwistStamped& msg)
{
  //NOTE:: rostopic pub -s -r  1 /anemometer/data geometry_msgs/TwistStamped "header: auto twist:
  ad_.msgs.push_back(msg);

  u_int32_t now= ros::Time::now().sec;

  // Keep the most recent measurements received within the last max_data_age_ seconds
  for (auto it = ad_.msgs.begin(); it != ad_.msgs.end(); ++it) 
  { 
    if (now - (*it).header.stamp.sec > max_data_age_) 
    { 
      ad_.msgs.erase(it); 
      it--; 
    } 
  } 

  ad_.msg_count= ad_.msgs.size();
  ad_.msg_freq= double(ad_.msg_count) / double(max_data_age_);
}

void 
SLNode::gasSensorCB(const std_msgs::Float32& msg)
{

}

//Descrip
void 
SLNode::requestMap()
{
  // Service request for a static map from the map server
  nav_msgs::GetMap::Request req;
  // Service response hopefully containing the static map from the map server
  nav_msgs::GetMap::Response resp;
  ROS_INFO("Requesting the map...");
  while(!ros::service::call("static_map", req, resp))
  {
    ROS_WARN("Request for map failed; trying again...");
    ros::Duration d(0.5);
    d.sleep();
  }

  handleMapMessage(resp.map);
}

// The callback for the map subscription 
void 
SLNode::mapReceived(const nav_msgs::OccupancyGridConstPtr& msg)
{
  if(first_map_only_ && first_map_received_) 
  {
    return;
  }

  handleMapMessage(*msg);

  first_map_received_ = true;

}

//Descrip
void
SLNode::handleMapMessage(const nav_msgs::OccupancyGrid& msg)
{
  ROS_INFO("Received a %d X %d map @ %.3f m/pix\n",
           msg.info.width,
           msg.info.height,
           msg.info.resolution);
  
  if(msg.header.frame_id != global_frame_id_)
    ROS_WARN("Frame_id of map received:'%s' doesn't match global_frame_id:'%s'. This could cause issues with reading published topics",
             msg.header.frame_id.c_str(),
             global_frame_id_.c_str());

  //freeMapDependentMemory();
  
  map_ = load_map_t(msg);

  // Create the particle filter
  pf_alloc(pf_, min_particles_, max_particles_);

  // Initialize the filter
  pf_init_uniform(pf_, map_, z_min_, z_max_, rate_min_, rate_max_);
  pf_init_= false;

}

