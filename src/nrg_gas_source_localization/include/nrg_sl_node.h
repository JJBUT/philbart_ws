#ifndef NRG_SL_NODE_H
#define NRG_SL_NODE_H

//https://answers.ros.org/question/280856/synchronizer-with-approximate-time-policy-in-a-class-c/

#include <gmx200_anemometer/AnemometerMsg.h>

#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

//using AnemometerMsg = gmx200_anemometer::AnemometerMsg;
typedef gmx200_anemometer::AnemometerMsg AnemometerMsg;
typedef gmx200_anemometer::AnemometerMsgConstPtr AnemometerMsgConstPtr;

class NRGSLNode{
    ros::NodeHandle nh;
    message_filters::Subscriber<AnemometerMsg> sub1;
    message_filters::Subscriber<AnemometerMsg> sub2; 
    typedef message_filters::sync_policies::ApproximateTime<AnemometerMsg, AnemometerMsg> MySyncPolicy;
    typedef message_filters::Synchronizer<MySyncPolicy> Sync;
    boost::shared_ptr<Sync> sync;
public:
    NRGSLNode();
    void callback(const AnemometerMsgConstPtr &msg1, const AnemometerMsgConstPtr &msg2);
};


#endif  //NRG_SL_NODE_H