#include "particle_filter.h"

ParticleFilter::ParticleFilter(){
};

ParticleFilter::ParticleFilter(int np, state_space ss, wind_model wm): ss_{ss}, wm_{wm} {
    initialize();
};

void ParticleFilter::initialize(int np, state_space ss, wind_model wm){

    ss_=ss;
    wm_=wm;
};

void ParticleFilter::initialize(){
    
};












int main(){
    return 0;
}