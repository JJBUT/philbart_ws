#include <nrg_gas_concentration_server/nrg_gas_concentration_server.h>

namespace nrg_gas_concentration_server
{
    SimulatedSourceServer::SimulatedSourceServer()
    : private_nh_("~")
    {
        // set_gas_source_srv_ = private_nh_.advertiseService( "set_source", 
        //                                                     &SimulatedSourceServer::addSource, 
        //                                                     this);

        // get_concentration_srv_ = private_nh_.advertiseService( "get_concentration", 
        //                                                &SimulatedSourceServer::getConcentration, 
        //                                                this);
                                                       
        // clear_sources_srv_ = private_nh_.advertiseService( "clear_sources", 
        //                                            &SimulatedSourceServer::clearSources, 
        //                                            this);

    }
};
