#include <nrg_gas_concentration_server/nrg_gas_concentration_server.h>
#include <nrg_gas_source_localization/nrg_sl_utils.h>

#include <ros/console.h>

#include <iostream> //TODO remove

namespace nrg_gas_concentration_server
{
    SimulatedSourceServer::SimulatedSourceServer()
    : private_nh_("~"),
      initialized_{false}
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
      if ( req.data.ya >= 0 &&
           req.data.yb >= 0 &&
           req.data.yc >= 0 &&
           req.data.za >= 0 &&
           req.data.zb >= 0 &&
           req.data.zc >= 0 )
      {
        wp_ = req.data;
        initialized_ = true;
        res.success = true;
        return 1;
      } 
      else 
      {
        initialized_ = false;
        res.success = false;
        return 1;
      }
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
      res.concentration = 0.0;
      //TODO-add check for initialization
      const std::lock_guard<std::mutex> lock(sources_mutex_);
      std::vector<double> source_local_measurement_point(3);
      std::vector<double> measurement_point(3);
      measurement_point[0] = req.gas_sensor_position.point.x;
      measurement_point[1] = req.gas_sensor_position.point.y;
      measurement_point[2] = req.gas_sensor_position.point.z;
      
      for(const auto &s: sources_)
      {
        std::vector<double> source_point(3);
        source_point[0] = s.position.point.x;
        source_point[1] = s.position.point.y;
        source_point[2] = s.position.point.z;

        pf::transform( source_local_measurement_point, 
                       measurement_point, 
                       source_point, 
                       req.wind_azimuth);

        if( source_local_measurement_point[0]<0 )
        {
            //Downwind concentration is zero if source local measurement point is not downwind of source 
            res.concentration += 0.0;
        }else{
            const double sy = wp_.ya*source_local_measurement_point[0]*std::pow( 1.0+wp_.yb*source_local_measurement_point[0], -wp_.yc );
            const double sz = wp_.za*source_local_measurement_point[0]*std::pow( 1.0+wp_.zb*source_local_measurement_point[0], -wp_.zc );
            const double expy = std::exp(-( source_local_measurement_point[1]*source_local_measurement_point[1] )/( 2*sy*sy ));  
            const double expz = std::exp(-( source_local_measurement_point[2]*source_local_measurement_point[2] )/( 2*sz*sz ));
            const double norm = ( s.rate/req.wind_speed )/( 2*M_PI*sy*sz );
            res.concentration += norm*expy*expz;
        }
      }
      return 1;
    }

    bool SimulatedSourceServer::clearSources( std_srvs::Empty::Request &req, 
                                              std_srvs::Empty::Response &res ) 
    {
      const std::lock_guard<std::mutex> lock(sources_mutex_);

      sources_.clear();

      return 1;
    }
};

