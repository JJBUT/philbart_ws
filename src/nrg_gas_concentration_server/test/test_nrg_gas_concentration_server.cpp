#include "nrg_gas_concentration_server/nrg_gas_concentration_server.h"

#include <gtest/gtest.h>


using namespace nrg_gas_concentration_server;

class NRGGasConcentrationServiceTests: public ::testing::Test 
{
protected: 
  void SetUp() override
  {

    ros::service::waitForService("/nrg_gas_concentration_server/set_wind_params", 5);
    set_wind_params_client = nh.serviceClient<SetWindParams>("/nrg_gas_concentration_server/set_wind_params");

    ros::service::waitForService("/nrg_gas_concentration_server/set_source", 5);
    set_gas_source_client = nh.serviceClient<SetSource>("/nrg_gas_concentration_server/set_source");

    ros::service::waitForService("/nrg_gas_concentration_server/get_concentration", 5);
    get_concentration_client = nh.serviceClient<GetConcentration>("/nrg_gas_concentration_server/get_concentration");

    ros::service::waitForService("/nrg_gas_concentration_server/clear_sources", 5);
    clear_sources_client = nh.serviceClient<std_srvs::Empty>("/nrg_gas_concentration_server/clear_sources");
    
  }

  ros::NodeHandle nh;
  ros::ServiceClient set_wind_params_client,
                     set_gas_source_client, 
                     get_concentration_client, 
                     clear_sources_client;
};

TEST_F(NRGGasConcentrationServiceTests, SetPositiveWindParams)
{
  SetWindParams srv;
  srv.request.data.ya = 1.1;
  srv.request.data.za = 2.2;

  set_wind_params_client.call(srv);
  EXPECT_EQ(srv.response.success, true);
}

TEST_F(NRGGasConcentrationServiceTests, SetNegativeWindParams)
{
  SetWindParams srv;
  srv.request.data.ya = -1.1;
  srv.request.data.za = -2.2;

  set_wind_params_client.call(srv);
  EXPECT_EQ(srv.response.success, false);
}

TEST_F(NRGGasConcentrationServiceTests, SetZeroWindParams)
{
  SetWindParams srv;

  set_wind_params_client.call(srv);
  EXPECT_EQ(srv.response.success, true);
}

TEST_F(NRGGasConcentrationServiceTests, AddPositiveRateSource)
{
  SetSource srv;
  srv.request.source.rate = 10.0;

  set_gas_source_client.call(srv);
  EXPECT_EQ(srv.response.success, true);
}

TEST_F(NRGGasConcentrationServiceTests, AddNegativeRateSource)
{
  SetSource srv;
  srv.request.source.rate = -10.0;

  set_gas_source_client.call(srv);
  EXPECT_EQ(srv.response.success, false);
}

TEST_F(NRGGasConcentrationServiceTests, AddZeroRateSource)
{
  SetSource srv;
  srv.request.source.rate = 0.0;

  set_gas_source_client.call(srv);
  EXPECT_EQ(srv.response.success, false);
}

TEST_F(NRGGasConcentrationServiceTests, CalculateDownwindConcentration)
{

  std_srvs::Empty srv;
  clear_sources_client.call(srv);

  SetWindParams srv1;
  srv1.request.data.ya = 0.22;
  srv1.request.data.yb = 0.0001;
  srv1.request.data.yc = 0.5;
  srv1.request.data.za = 0.2;
  srv1.request.data.zb = 0.0;
  srv1.request.data.zc = 0.0;
  set_wind_params_client.call(srv1);

  SetSource srv2;
  srv2.request.source.rate = 12000.0;
  srv2.request.source.position.point.x = -10.0;
  srv2.request.source.position.point.y = 20.0;
  srv2.request.source.position.point.z = 0.0;
  set_gas_source_client.call(srv2);

  GetConcentration srv3;
  srv3.request.gas_sensor_position.point.x = -18.5;
  srv3.request.gas_sensor_position.point.y = -19.225504059505997;
  srv3.request.gas_sensor_position.point.z = 0.0;
  srv3.request.wind_azimuth = -2.0;
  srv3.request.wind_speed = 1.0;
  get_concentration_client.call(srv3);

  EXPECT_NEAR(0.1, srv3.response.concentration, 17.189372090029856);
}


TEST_F(NRGGasConcentrationServiceTests, CalculateUpwindConcentration)
{
  std_srvs::Empty srv;
  clear_sources_client.call(srv);

  SetWindParams srv1;
  srv1.request.data.ya = 0.22;
  srv1.request.data.yb = 0.0001;
  srv1.request.data.yc = 0.5;
  srv1.request.data.za = 0.2;
  srv1.request.data.zb = 0.0;
  srv1.request.data.zc = 0.0;
  set_wind_params_client.call(srv1);

  SetSource srv2;
  srv2.request.source.rate = 12000.0;
  srv2.request.source.position.point.x = -10.0;
  srv2.request.source.position.point.y = 20.0;
  srv2.request.source.position.point.z = 0.0;
  set_gas_source_client.call(srv2);

  GetConcentration srv3;
  srv3.request.gas_sensor_position.point.x = -9.0;
  srv3.request.gas_sensor_position.point.y = 21.0;
  srv3.request.gas_sensor_position.point.z = 0.0;
  srv3.request.wind_azimuth = -2.0;
  srv3.request.wind_speed = 1.0;
  get_concentration_client.call(srv3);

  EXPECT_EQ(0, srv3.response.concentration);
}


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  ros::init(argc, argv, "test_nrg_gas_concentration_server");
  return RUN_ALL_TESTS();
}
