#include <nrg_sl_data_test_node.h>
#include <nrg_gas_source_localization/nrg_sl_utils.h>


NRGSLdata_testNODE::NRGSLdata_testNODE()
: nh_(),
  pub_wind_{nh_.advertise< AnemometerMsg >( "anemometer_data", 5 )},
  pub_gas_{nh_.advertise< MG811Msg >( "gas_sensor_data", 5 )}
{
    return;
}

void NRGSLdata_testNODE::setMeasurementData( std::string path )
{
    this->measurement_data = pf::read_data("/home/jacksubuntu/philbart_ws/src/nrg_gas_source_localization/data/one_source/a_data_matlab.txt");      
    return;
}

void NRGSLdata_testNODE::pubMeasurement()
{
    return;
}

////////////////Entry Point/////////////////
int main(int argc, char** argv)
{
  ros::init(argc, argv, "nrg_data_test_source_localization_node");

  NRGSLdata_testNODE test_node;

  ROS_INFO_STREAM("spining");
  ros::spin();
  
  return(0);
}