#include "random"
#include "algorithm" //std::generate()
#include "iostream"

#include "particle_filter.h"

ParticleFilter::ParticleFilter(): initialized{false}{
};

ParticleFilter::ParticleFilter(int np, state_space ss, wind_model wm): ss_{ss}, wm_{wm} {
    initialize(np);
};

ParticleFilter::~ParticleFilter(){
};



void ParticleFilter::initialize(int np, state_space ss, wind_model wm){
    if(initialized == false){
        ps.particles.resize(np);
        ps.np= np;
        ss_= ss;
        wm_= wm;

        for(auto& p: ps.particles){
            p.weight=1.0/np;
            auto rnv= pf::uniform_rnv(4);
            p.position[0]= ss_.x[0]+rnv[0]*(ss_.x[1]-ss_.x[0]);
            p.position[1]= ss_.y[0]+rnv[1]*(ss_.y[1]-ss_.y[0]);
            p.position[2]= ss_.z[0]+rnv[2]*(ss_.z[1]-ss_.z[0]);
            p.rate= ss_.rate[0]+rnv[3]*(ss_.rate[1]-ss_.rate[0]);
        }
        initialized= true;
    }
 
    return;
};

void ParticleFilter::initialize(int np){
    ps.particles.resize(np);
    ps.np= np;

    for(auto& p: ps.particles){
        p.weight=1.0/np;
        auto rnv= pf::uniform_rnv(4);
        p.position[0]= ss_.x[0]+rnv[0]*(ss_.x[1]-ss_.x[0]);
        p.position[1]= ss_.y[0]+rnv[1]*(ss_.y[1]-ss_.y[0]);
        p.position[2]= ss_.z[0]+rnv[2]*(ss_.z[1]-ss_.z[0]);
        p.rate= ss_.rate[0]+rnv[3]*(ss_.rate[1]-ss_.rate[0]);
    }
    
    initialized= true;
    return;
};



int main(){
    wind_model fake_wind_model;
    state_space fake_state_space(-10,10,-10,10,-10,10,0.0,500);
    measurement fake_measurement;

    //ParticleFilter fake_particle_filter(20, fake_state_space, fake_wind_model);
    ParticleFilter fake_particle_filter;
    fake_particle_filter.initialize(10, fake_state_space, fake_wind_model);
    
    return 0;
}


namespace pf{
std::vector<double> uniform_rnv(int count)
{   
    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};  // Generates random doubles
    std::uniform_real_distribution<double> dist (0, 1.0);
    auto gen = [&dist, &mersenne_engine](){return dist(mersenne_engine);};

    std::vector<double> rnv(count);
    std::generate(rnv.begin(), rnv.end(), gen);

    return rnv;
}
} //END of pf namespace