#ifndef NRG_SL_DATA_TEST_NODE_H
#define NRG_SL_DATA_TEST_NODE_H

#include <gmx200_anemometer/AnemometerMsg.h>
#include <mg_811_co2_sensor/MG811Msg.h>

#include <ros/ros.h>

#include <vector>
#include <string>

using gmx200_anemometer::AnemometerMsg;
using mg_811_co2_sensor::MG811Msg;


class NRGSLdata_testNODE{
    ros::NodeHandle nh_;
    ros::Publisher pub_wind_;
    ros::Publisher pub_gas_;

    std::vector< std::vector<double> > measurement_data;
public:
    NRGSLdata_testNODE();
    void setMeasurementData( std::string path );
    void pubMeasurement();

};
#endif //NRG_SL_DATA_TEST_NODE_H