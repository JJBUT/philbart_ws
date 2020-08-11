#include <nrg_sl_data_test_node.h>
#include <nrg_gas_source_localization/nrg_sl_utils.h>

#include <gmx200_anemometer/AnemometerMsg.h>
#include <mg_811_co2_sensor/MG811Msg.h>

#include <std_msgs/Header.h>
#include <tf2/LinearMath/Quaternion.h>
#include <geometry_msgs/TransformStamped.h>


using gmx200_anemometer::AnemometerMsg;
using mg_811_co2_sensor::MG811Msg;

using std_msgs::Header;

NRGSLdata_testNODE::NRGSLdata_testNODE()
: nh_(),
  pub_wind_{nh_.advertise< AnemometerMsg >( "anemometer_data", 5 )},
  pub_gas_{nh_.advertise< MG811Msg >( "gas_sensor_data", 5 )}
{
    setMeasurementData("/home/jacksubuntu/philbart_ws/src/nrg_gas_source_localization/data/one_source/a_data_matlab.txt");
    return;
}

void NRGSLdata_testNODE::setMeasurementData( std::string path )
{
    measurement_data = pf::read_data( path );      
    return;
}

void NRGSLdata_testNODE::pubMeasurement()
{
    ros::Time current_time = ros::Time::now();

    Header wind_header; 
           wind_header.seq = 0; 
           wind_header.stamp = current_time;
           wind_header.frame_id = "anemometer_link";
    AnemometerMsg wind_msg;
                  wind_msg.header = wind_header;
                  wind_msg.azimuth = measurement_data[0][5];
                  wind_msg.speed = measurement_data[0][4];

    Header gas_header;
           gas_header.seq = 0;
           gas_header.stamp = current_time;
           gas_header.frame_id = "gas_sensor_link";
    MG811Msg gas_msg;
             gas_msg.header = gas_header;
             gas_msg.concentration = measurement_data[0][3];

    geometry_msgs::TransformStamped measurementLocation;
    measurementLocation.header.stamp = current_time;
    measurementLocation.header.frame_id = "map";
    measurementLocation.child_frame_id = "base_link";
    measurementLocation.transform.translation.x = measurement_data[0][0];
    measurementLocation.transform.translation.y = measurement_data[0][1];
    measurementLocation.transform.translation.z = measurement_data[0][2];
    tf2::Quaternion q;
    q.setRPY(0, 0, 0);
    measurementLocation.transform.rotation.x = q.x();
    measurementLocation.transform.rotation.y = q.y();
    measurementLocation.transform.rotation.z = q.z();
    measurementLocation.transform.rotation.w = q.w();
    

    measurement_data.erase( measurement_data.begin() );

    pub_wind_.publish(wind_msg);
    pub_gas_.publish(gas_msg);
    pub_tf_.sendTransform(measurementLocation);

    return;
}

////////////////Entry Point/////////////////
int main(int argc, char** argv)
{
    ros::init(argc, argv, "nrg_data_test_source_localization_node");

    NRGSLdata_testNODE test_node;

    ros::Rate r(2.0); 
    while (1)
    {
        test_node.pubMeasurement();
        ros::spinOnce();
        r.sleep();
    }

  
  return(0);
}