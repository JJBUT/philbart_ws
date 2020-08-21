#ifndef NRG_GAS_CONCENTRATION_SERVER_H
#define NRG_GAS_CONCENTRATION_SERVER_H


#include <ros/ros.h>
#include <std_srvs/Empty.h>

#include <nrg_gas_concentration_server/GasSource.h>
#include <nrg_gas_concentration_server/SetWindParams.h>
#include <nrg_gas_concentration_server/SetSource.h>
#include <nrg_gas_concentration_server/GetConcentration.h>

#include <vector>
#include <mutex>


namespace nrg_gas_concentration_server
{

class SimulatedSourceServer
{
    bool setWindParams( SetWindParams::Request &req, 
                        SetWindParams::Response &res );

    bool addSource( SetSource::Request &req, 
                    SetSource::Response &res );

    bool getConcentration( GetConcentration::Request &req, 
                           GetConcentration::Response &res );

    bool clearSources( std_srvs::Empty::Request &req, 
                       std_srvs::Empty::Response &res );

    std::vector<GasSource> sources_;

    mutable std::mutex sources_mutex_;

    ros::NodeHandle private_nh_;

    ros::ServiceServer set_wind_params_srv_,
                       set_gas_source_srv_, 
                       get_concentration_srv_, 
                       clear_sources_srv_ ;
public:
    SimulatedSourceServer();

    GasSource& getSource(int i);

    int getSize();





};



} // nrg_gas_concentration_server


#endif