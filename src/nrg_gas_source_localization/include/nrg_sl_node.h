#ifndef NRG_SL_NODE_H
#define NRG_SL_NODE_H

//https://answers.ros.org/question/280856/synchronizer-with-approximate-time-policy-in-a-class-c/

#include <nrg_gas_source_localization/nrg_sl_particle_filter.h>
#include <gmx200_anemometer/AnemometerMsg.h>
#include <mg_811_co2_sensor/MG811Msg.h>

#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>


#include <string>

using gmx200_anemometer::AnemometerMsg;
using gmx200_anemometer::AnemometerMsgConstPtr;
using mg_811_co2_sensor::MG811Msg;
using mg_811_co2_sensor::MG811MsgConstPtr;

class NRGSLNode{
    ros::NodeHandle nh_;
    ros::NodeHandle private_nh_;

    ParticleFilter filter_;

    message_filters::Subscriber<AnemometerMsg> sub_wind;
    message_filters::Subscriber<MG811Msg> sub_gas; 
    typedef message_filters::sync_policies::ApproximateTime<AnemometerMsg, MG811Msg> MySyncPolicy;
    typedef message_filters::Synchronizer<MySyncPolicy> Sync;
    boost::shared_ptr<Sync> sync;

    


public:
    NRGSLNode();
    void callback(const AnemometerMsgConstPtr &msg1, const MG811MsgConstPtr &msg2);
};


#endif  //NRG_SL_NODE_H