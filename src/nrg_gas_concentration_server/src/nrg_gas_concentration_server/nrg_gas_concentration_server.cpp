#include <nrg_gas_concentration_server/nrg_gas_concentration_server.h>

#include <ros/console.h>

#include <iostream> //TODO remove

namespace nrg_gas_concentration_server
{
    SimulatedSourceServer::SimulatedSourceServer()
    : private_nh_("~")
    { 
        set_wind_params_srv_ = private_nh_.advertiseService( "set_wind_params", 
                                                             &SimulatedSourceServer::setWindParams, 
                                                             this );

        set_gas_source_srv_ = private_nh_.advertiseService( "set_source", 
                                                             &SimulatedSourceServer::addSource, 
                                                             this );

        get_concentration_srv_ = private_nh_.advertiseService( "get_concentration", 
                                                               &SimulatedSourceServer::getConcentration, 
                                                               this );
                                                       
        clear_sources_srv_ = private_nh_.advertiseService( "clear_sources", 
                                                           &SimulatedSourceServer::clearSources, 
                                                           this );

    }

    bool SimulatedSourceServer::setWindParams( SetWindParams::Request &req, 
                                               SetWindParams::Response &res )
    {
      res.success = true;
      return 1;
    }


    bool SimulatedSourceServer::addSource( SetSource::Request &req, 
                                           SetSource::Response &res ) 
    {
      const std::lock_guard<std::mutex> lock( sources_mutex_ );
            
      if ( req.source.rate <= 0 ) 
      {
        ROS_DEBUG_STREAM_NAMED( "SimulatedSourceServer::addSource()", "Source rate must be positive" );
        res.success = 0;
        return 1;
      }
      sources_.push_back( req.source );
      res.success = 1;
      return 1;
    }

    bool SimulatedSourceServer::getConcentration( GetConcentration::Request &req, 
                                                  GetConcentration::Response &res ) 
    {
      const std::lock_guard<std::mutex> lock(sources_mutex_);

      return 1;
    }

    bool SimulatedSourceServer::clearSources( std_srvs::Empty::Request &req, 
                                              std_srvs::Empty::Response &res ) 
    {
      const std::lock_guard<std::mutex> lock(sources_mutex_);

      sources_.clear();

      return 1;
    }

    GasSource& SimulatedSourceServer::getSource(int i)
    {
      return sources_[i];
    }

    int SimulatedSourceServer::getSize()
    {
      return sources_.size();
    }
};

