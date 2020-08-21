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


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  ros::init(argc, argv, "test_nrg_gas_concentration_server");
  return RUN_ALL_TESTS();
}
