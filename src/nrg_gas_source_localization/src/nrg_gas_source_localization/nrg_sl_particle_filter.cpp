#include <nrg_gas_source_localization/nrg_sl_particle_filter.h>
#include <nrg_gas_source_localization/nrg_sl_utils.h>


#include <cmath>

ParticleFilter::ParticleFilter(): initialized{false}{
};

ParticleFilter::ParticleFilter(pf_params pfp, state_space ss, wind_model wm): pfp_{pfp}, ss_{ss}, wm_{wm} {
    initialize();
};


void ParticleFilter::initialize(pf_params pfp, state_space ss, wind_model wm){
    if( initialized == false )
    {
        pfp_ = pfp;
        ss_ = ss;
        wm_ = wm;

        ps.particles.resize(pfp_.np);
        for( auto& p: ps.particles )
        {
            p.weight = 1.0/pfp_.np;

            auto rnv = pf::uniform_rn(4);
            p.position[0] = ss_.x[0] + rnv[0]*(ss_.x[1] - ss_.x[0]);
            p.position[1] = ss_.y[0] + rnv[1]*(ss_.y[1] - ss_.y[0]);
            p.position[2] = ss_.z[0] + rnv[2]*(ss_.z[1] - ss_.z[0]);
            p.rate = ss_.rate[0] + rnv[3]*(ss_.rate[1] - ss_.rate[0]);
        }
        initialized= true;
    }
    return;
};

void ParticleFilter::initialize(){
    ps.particles.resize( pfp_.np );

    for( auto &p: ps.particles )
    {
        p.weight = 1.0/pfp_.np;
        
        auto rnv = pf::uniform_rn(4);
        p.position[0] = ss_.x[0] + rnv[0]*(ss_.x[1] - ss_.x[0]);
        p.position[1] = ss_.y[0] + rnv[1]*(ss_.y[1] - ss_.y[0]);
        p.position[2] = ss_.z[0] + rnv[2]*(ss_.z[1] - ss_.z[0]);
        p.rate = ss_.rate[0] + rnv[3]*(ss_.rate[1] - ss_.rate[0]);
    }
    initialized= true;
    return;
};

void ParticleFilter::updateFilter(measurement z){
    if ( initialized == true )
    {
        predict(z);
        reweight(z);
        if ( isDegenerate() )
        { 
            resample();
        }    
        return;
    }
    throw "ParticleFilter::updateFilter()";
    return;
}

void ParticleFilter::predict( measurement z ){
    double source_local_measurement_point[3] = { 0, 0, 0 };    //Measurement location in source particle frame //TODO fix up comment
    
    for( auto &p: ps.particles )
    {
        pf::transform( source_local_measurement_point, z.location, p.position, z.az );

        if( source_local_measurement_point[0]<0 )
        {
            //Downwind concentration is zero if test point is not downwind of source
            p.downwind_conc = 0.0;
        }else{
            double sy = wm_.sy[0]*source_local_measurement_point[0]*std::pow( 1.0+wm_.sy[1]*source_local_measurement_point[0], -wm_.sy[2] );
            double sz = wm_.sz[0]*source_local_measurement_point[0]*std::pow( 1.0+wm_.sz[1]*source_local_measurement_point[0], -wm_.sz[2] );
            double expy = std::exp(-std::pow( source_local_measurement_point[1], 2 )/( 2*std::pow(sy, 2) ));
            double expz = std::exp(-std::pow( source_local_measurement_point[2], 2 )/( 2*std::pow(sz, 2) ));
            double norm = ( p.rate/z.vel )/( 2*M_PI*sy*sz );
            p.downwind_conc = norm*expy*expz;
        }
    }
    return;
}

void ParticleFilter::reweight( measurement z ){
    double max_weight = 0.0;
    // Reweight particles based on similarity between measured concentration and predicted concentration
    for( auto &p: ps.particles )
    {
        p.weight *= pf::gaussian( p.downwind_conc, z.conc, pfp_.R );    //TODO check multiply equal
        if( p.weight > max_weight ) max_weight = p.weight;
    }
    
    // Log-likelihood reweight to prevent numerical underflow
    double weight_sum = 0;
    for( auto &p: ps.particles )
    {
        p.weight = std::exp( std::log(p.weight/max_weight) );
        weight_sum += p.weight; 
    }
    
    // Normalize the cdf to 1
    for( auto &p: ps.particles )
    {
        p.weight /= weight_sum;
    }
    return;
}

void ParticleFilter::resample(){
    // See Multinomial Resampling in: "Particle filters and resampling techniques: Importance in computational complexity analysis" IEEE 2013
    particle_set new_ps;
    new_ps.particles.resize( pfp_.np );
    
    // Find incremental sum of weight vector
    std::vector<double> weight_sum{0.0};    //Final size will be np+1 elements
    for( const auto &p: ps.particles ){
        weight_sum.push_back( weight_sum.back() + p.weight ); 
    }
    
    // Pick a new particles from old particle set 
    for( auto &new_p: new_ps.particles )
    {        
        double pick = pf::uniform_rn();
        for(int i = 0; i < pfp_.np; i++)
        {
            if( pick > weight_sum[i] &&
                pick < weight_sum[i+1] )
            {
                new_p = ps.particles[i];
                new_p.weight = 1.0/pfp_.np;
                new_p.position[0] += pf::uniform_rn()*pfp_.Q;
                new_p.position[1] += pf::uniform_rn()*pfp_.Q;
                new_p.position[2] += pf::uniform_rn()*pfp_.Q;
            }
        }
    }
    ps = new_ps;
    return;
}

bool ParticleFilter::isDegenerate() const{
    double sum = 0;
    for( auto &p: ps.particles )
    {
        sum += std::pow( p.weight, 2 );
    }
    
    if( 1.0/sum < pfp_.np_min )
    {    
        // Degenerate
        return true;
    }
    // Not degenerate
    return false;
}

void ParticleFilter::printStatistics() const{
    std::vector<double> mean(4,0);
    for(auto &p: ps.particles)
    {
        mean[0] += p.position[0]/pfp_.np;
        mean[1] += p.position[1]/pfp_.np;
        mean[2] += p.position[2]/pfp_.np;
        mean[3] += p.rate/pfp_.np;
    }
}
/////////////Playpen Start/////////////


    // wind_model fake_wind_model( 0.22, 0.0001, 0.5, 0.20, 0.0, 0.0 );
    // state_space fake_state_space( -50.0, 50.0, -50.0, 50.0, -1.0, 1.0, 0.0, 20000.0 );
    // measurement fake_measurement( 0.0, 1.0, 500, 11199000 );
    // fake_measurement.location[0]= 2.0;
    // fake_measurement.location[1]= 0.0;
    // fake_measurement.location[2]= 0.0;
    // pf_params fake_pf_params;
    // fake_pf_params.np = 3000;
    // fake_pf_params.np_min = 2000;
    // fake_pf_params.R = 1.0;
    // fake_pf_params.Q = 0.1;


    // std::vector< std::vector<double> > measurements= read_data("/home/jacksubuntu/philbart_ws/src/nrg_gas_source_localization/data/one_source/a_data_matlab.txt");
    // for(auto& m: measurements){
    //     measurement fake_measurement( m[5], m[4], m[3], 0 );
    //     fake_measurement.location[0]= m[0];
    //     fake_measurement.location[1]= m[1];
    //     fake_measurement.location[2]= m[2];
    //     fake_particle_filter.printStatistics();
    //     fake_particle_filter.updateFilter(fake_measurement);
    // }



/////////////Playpen End/////////////
