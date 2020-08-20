#ifndef NRG_GAS_CONCENTRATION_SERVER_H
#define NRG_GAS_CONCENTRATION_SERVER_H

#include <vector>
#include <ros/ros.h>
#include <std_srvs/Empty.h>

#include <nrg_gas_concentration_server/GasSource.h>
#include <nrg_gas_concentration_server/SetSource.h>
#include <nrg_gas_concentration_server/GetConcentration.h>


namespace nrg_gas_concentration_server
{

class SimulatedSourceServer
{
    std::vector<double> sources_;

    bool addSource( SetSource::Request &req, 
                    std_srvs::Empty::Response &res );

    bool getConcentration( GetConcentration::Request &req, 
                           GetConcentration::Response &res);

    bool clearSources( std_srvs::Empty::Request &req, 
                       std_srvs::Empty::Response &res);

    ros::NodeHandle private_nh_;

    ros::ServiceServer set_gas_source_srv_, 
                       get_concentration_srv_, 
                       clear_sources_srv_ ;



public:
    SimulatedSourceServer();

};



} // nrg_gas_concentration_server


#endif