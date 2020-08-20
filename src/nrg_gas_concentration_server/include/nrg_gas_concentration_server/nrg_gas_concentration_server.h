#ifndef NRG_GAS_CONCENTRATION_SERVER_H
#define NRG_GAS_CONCENTRATION_SERVER_H

#include <vector>
#include <ros/ros.h>
#include "nrg_gas_concentration_server/SetSource.h"
#include "nrg_gas_concentration_server/GetConcentration.h"
#include "nrg_gas_concentration_server/ClearSources.h"

namespace nrg_gas_concentration_server
{

class SimulatedSourceServer
{
    std::vector<double> sources_;

    bool addSource( SetSource::SetSource &req, 
                    SetSource::SetSource &res );

    bool getConcentration( GetConcentration::GetConcentration &req, 
                           GetConcentration::GetConcentration &res);

    bool clearSources( ClearSources::ClearSources &req, 
                       ClearSources::ClearSources &res);

    ros::NodeHandle private_nh_;

    ros::ServiceServer set_gas_source_srv_, 
                       get_concentration_srv_, 
                       clear_sources_srv_ ;



public:
    SimulatedSourceServer();

};



} // nrg_gas_concentration_server


#endif