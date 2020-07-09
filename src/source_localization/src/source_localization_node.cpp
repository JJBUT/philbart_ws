/*Author Jack Borer*/

//Standard library
#include "iostream"
#include "memory" //smart pointers

//roscpp
#include "ros/ros.h"

//Required ROS msgs
#include "std_msgs/String.h"


namespace sl{

//Pose hypothesis

static const std::string anemometer_topic_ = "anemometer/data";
static const std::string gas_sensor_topic_ = "gas_sensor/data";
static const std::string pose_topic_ = "odometry/filtered_map";

class SourceLocalizationNode
{
    public:
        SourceLocalizationNode();
        ~SourceLocalizationNode();

    private:   
  
};

} //END sl:: namespace

int main()
{
  return(0);
}