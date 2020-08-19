#ifndef NRG_GAS_CONCENTRATION_SERVER_H
#define NRG_GAS_CONCENTRATION_SERVER_H

#include <vector>
#include <ros/ros.h>

namespace nrg_gas_concentration_server
{

class SimulatedSourceServer
{
    std::vector<double> sources_;

    void addSource();

    void getConcentration();

    void clearSources();

    ros::NodeHandle private_nh_;

    ros::ServiceServer set_gas_source_srv_, 
                       get_concentration_srv_, 
                       clear_sources_srv_ ;



public:
    SimulatedSourceServer();

};



} // nrg_gas_concentration_server


#endif