#include <nrg_gas_concentration_server/nrg_gas_concentration_server.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "simulated_gas_concentration_server");

  nrg_gas_concentration_server::SimulatedSourceServer node;
  
  ros::spin();

  return 0;
}