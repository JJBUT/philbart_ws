#include "random"
#include "algorithm" //std::generate()
#include "iostream"
#include "cmath"

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
            auto rnv= pf::uniform_rn(4);
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
        auto rnv= pf::uniform_rn(4);
        p.position[0]= ss_.x[0]+rnv[0]*(ss_.x[1]-ss_.x[0]);
        p.position[1]= ss_.y[0]+rnv[1]*(ss_.y[1]-ss_.y[0]);
        p.position[2]= ss_.z[0]+rnv[2]*(ss_.z[1]-ss_.z[0]);
        p.rate= ss_.rate[0]+rnv[3]*(ss_.rate[1]-ss_.rate[0]);
    }
    
    initialized= true;
    return;
};

void ParticleFilter::updateFilter(measurement z){
    predict(z);
    reweight(z);
    // if Neff<.5;{
    resample();
    // }
    
}

void ParticleFilter::predict(measurement z){
    double source_local_test_point[3];
    
    for(auto& p: ps.particles){
        pf::transform(source_local_test_point, z.location, p.position, z.az);

        if(source_local_test_point[0]<0){
            p.downwind_conc=0.0;
        }else{
            double sy= wm_.sy[0]*source_local_test_point[0]*std::pow(1+wm_.sy[1]*source_local_test_point[0], -wm_.sy[2]);;
            double sz= wm_.sz[0]*source_local_test_point[0]*std::pow(1+wm_.sz[1]*source_local_test_point[0], -wm_.sz[2]);;

            double expy= std::exp((std::pow(-source_local_test_point[1], 2))/(2*std::pow(source_local_test_point[1], 2)));
            double expz= std::exp((std::pow(-source_local_test_point[2], 2))/(2*std::pow(source_local_test_point[2], 2)));

            double norm= ((p.rate/z.vel)/(2*M_PI*sy*sz));

            p.downwind_conc= norm*expy*expz;
        }
    }
    return;
}

void ParticleFilter::reweight(measurement z){

    double max_weight=0.0;
    // Reweight using a gaussian and find the max weight value
    for(auto& p: ps.particles){
        std::cout<<"Reweight\n";
        p.weight= p.weight*pf::gaussian(p.downwind_conc, z.conc, ps.R);
        if(p.weight>max_weight) max_weight = p.weight;
    }

    // Calculate exponential of max weight adjusted log weight
    double weight_sum=0;
    for(auto& p: ps.particles){
        p.weight= std::exp(std::log(p.weight)-max_weight);
        weight_sum+=p.weight; 
    }

    // Renormalize the cdf to 1
    for(auto& p: ps.particles){
        p.weight/=weight_sum;
    }
    return;
}

void ParticleFilter::resample(){
    particle_set new_ps;
    new_ps.particles.resize(ps.np);
    new_ps.np= ps.np;
    new_ps.Neff= ps.Neff;
    new_ps.R= ps.R;
    
    std::vector<double> weight_sum{0.0};
    for(const auto& p: ps.particles){
        weight_sum.push_back(weight_sum.back()+p.weight); 
    }

    for(auto& new_p: new_ps.particles){
        double pick= pf::uniform_rn();
        for(int i=0; i<ps.np; i++){
            if(pick>weight_sum[i] && pick< weight_sum[i+1]){
                new_p= ps.particles[i];
            }
        }
    }
    ps= new_ps;

    return;
}


int main(){
    wind_model fake_wind_model;
    state_space fake_state_space(-10,10,-10,10,-10,10,0.0,500);
    measurement fake_measurement(0.0,1.0,45.5,11199000);
    fake_measurement.location[0]=2;
    fake_measurement.location[1]=0;
    fake_measurement.location[2]=0;

    ParticleFilter fake_particle_filter(20, fake_state_space, fake_wind_model);
    
    fake_particle_filter.updateFilter(fake_measurement);
    
    return 0;
}


namespace pf{
std::vector<double> uniform_rn(int count){   
    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};  // Generates random doubles
    std::uniform_real_distribution<double> dist (0, 1.0);
    auto gen = [&dist, &mersenne_engine](){return dist(mersenne_engine);};

    std::vector<double> rnv(count);
    std::generate(rnv.begin(), rnv.end(), gen);

    return rnv;
}

double uniform_rn(){   
    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};  // Generates random doubles
    std::uniform_real_distribution<double> dist (0, 1.0);
    
    return dist(mersenne_engine);
}

void transform(double source_local_test_point[3], const double test_point[3], const double source[3], const double& rotation){
    double temp_local[3];

    // Translation
    temp_local[0]= test_point[0] - source[0];
    temp_local[1]= test_point[1] - source[1];
    temp_local[2]= test_point[2] - source[2];

    // Rotation
    double R[3][3]= {};
    R[0][0]= cos(rotation);
    R[0][1]= -sin(rotation);
    R[1][0]= sin(rotation);
    R[1][1]= cos(rotation);
    R[2][2]= 1;

    // Recreate np.dot(local,R)
    
    for (size_t i = 0; i < 3; i++){ // Traverse the vector
        source_local_test_point[i]=0;
        for (size_t j = 0; j < 3; j++){ //Traverse the columns of the matrix
            source_local_test_point[i]+= temp_local[j] * R[j][i];
        }
    }

    return;
}

double gaussian(double x, double mu, double sigma){
    return (1/(std::sqrt(2*M_PI)*sigma))*std::exp(-0.5*std::pow((x-mu)/sigma, 2));
}

} //END of pf namespace