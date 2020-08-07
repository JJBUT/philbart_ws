#include <gmx200_anemometer/AnemometerMsg.h>

#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <memory>
#include <iostream>

//https://answers.ros.org/question/280856/synchronizer-with-approximate-time-policy-in-a-class-c/
using namespace gmx200_anemometer;


class Node
{
public:
  Node():
    p_nh{"~"}
  {
    sub1.subscribe(nh, "in1", 10);
    sub2.subscribe(nh, "in2", 10);
  }
  void callback(const AnemometerMsg &in1, const AnemometerMsg &in2)
  {
    std::cout<<"Msg one at time: "<<in1.header.stamp.sec<<" Msg two at time: "<<in2.header.stamp.sec<<std::endl;
  } 


private:
    ros::NodeHandle nh;
    ros::NodeHandle p_nh;
    message_filters::Subscriber<AnemometerMsg> sub1;
    message_filters::Subscriber<AnemometerMsg> sub2;
    typedef message_filters::sync_policies::ApproximateTime<AnemometerMsg, AnemometerMsg> MySyncPolicy;
    typedef message_filters::Synchronizer<MySyncPolicy> Sync;
    std::shared_ptr<Sync> sync;
};



int main(int argc, char** argv)
{
  ros::init(argc, argv, "amcl");
  Node synchronizer;

  ros::spin();
  
  return(0);
}