#include "cmath"
#include "iostream"

#include "predict.h"



Predict::Predict(const filter_state& filter, wind_model wm ):
    filter{filter},
    wm{wm}
{
    predicted_concentration.resize(filter.sets[0].particle_count);
}

Predict::~Predict(){}

void Predict::predictConcentration(const measurement& meas, const position& test_point)
{
    //Questions: is the tf fn. a potential inline candidate?
    //For particle in set 0, 
        //Convert the test point into a particle local frame using the azimuth and position data
        //Calculate the concentration that we predict we should sense at our curerent location
    std::cout<<"test point "<< test_point.pos[0]<<" "<< test_point.pos[1]<<" "<< test_point.pos[2]<<"\n"; 
    for (size_t i = 0; i < filter.sets[0].particle_count; i++)
    {
        position test_point_source_local= sl::transform(filter.sets[0].particles[i].p, test_point, meas.az);

        std::cout<<"source position: "<< filter.sets[0].particles[i].p.s[0]<<" "<<filter.sets[0].particles[i].p.s[1]<<" "<<filter.sets[0].particles[i].p.s[2]<<"\n";
        std::cout<<"test point source local: "<< test_point_source_local.pos[0]<<" "<<test_point_source_local.pos[1]<<" "<<test_point_source_local.pos[2]<<"\n";
    }
    
}

std::vector<double> Predict::getPredictedConcentrations() {return predicted_concentration;}


double Predict::sigma(const double wm_i[3], const position& local_test_point)
{
    double x= local_test_point.pos[0]; //Source local downwind distance x
    return wm_i[0]*x*std::pow(1+wm_i[1]*x,-wm_i[2]);
}