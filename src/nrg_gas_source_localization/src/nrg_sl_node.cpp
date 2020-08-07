#include <gmx200_anemometer/AnemometerMsg.h>

#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <memory>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

//https://answers.ros.org/question/280856/synchronizer-with-approximate-time-policy-in-a-class-c/
using namespace gmx200_anemometer;


class Node
{
public:
  Node()
  {
    sub1.subscribe(nh, "/in1", 10);
    sub2.subscribe(nh, "/in2", 10);
    sync.reset(new Sync(MySyncPolicy(10), sub1, sub2));   
    sync->registerCallback(boost::bind(&Node::callback, this, _1, _2));
  }

  void callback(const AnemometerMsgConstPtr &in1, const AnemometerMsgConstPtr &in2)
  {
    std::cout<<"Msg one at time: "<<in1->header.stamp.sec<<" Msg two at time: "<<in2->header.stamp.sec<<std::endl;
  } 

private:
    ros::NodeHandle nh;
    message_filters::Subscriber<AnemometerMsg> sub1;
    message_filters::Subscriber<AnemometerMsg> sub2;
    typedef message_filters::sync_policies::ApproximateTime<AnemometerMsg, AnemometerMsg> MySyncPolicy;
    typedef message_filters::Synchronizer<MySyncPolicy> Sync;
    boost::shared_ptr<Sync> sync;
};



int main(int argc, char** argv)
{
  ros::init(argc, argv, "amcl");
  Node synchronizer;

  ros::spin();
  
  return(0);
}