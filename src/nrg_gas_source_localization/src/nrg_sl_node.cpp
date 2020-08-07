#include <nrg_sl_node.h>

#include <iostream>

NRGSLNode::NRGSLNode()
{
  sub1.subscribe(nh, "/in1", 10);
  sub2.subscribe(nh, "/in2", 10);
  sync.reset(new Sync(MySyncPolicy(10), sub1, sub2));   
  sync->registerCallback(boost::bind(&NRGSLNode::callback, this, _1, _2));
}

void NRGSLNode::callback(const AnemometerMsgConstPtr &in1, const AnemometerMsgConstPtr &in2)
{
} 


int main(int argc, char** argv)
{
  ros::init(argc, argv, "nrg_sl_node");
  NRGSLNode synchronizer;

  ros::spin();
  
  return(0);
}