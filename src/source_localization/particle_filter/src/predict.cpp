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
    for (size_t i = 0; i < filter.sets[0].particle_count; i++)
    {
        state source = filter.sets[0].particles[i].p;
        position test_point_source_local= sl::transform(source, test_point, meas.az);
        
        if (test_point_source_local.pos[0]<0.0)
        {
            predicted_concentration[i]=0; //Downwind sources cannot produce concentration at upwind locations
        }else
        {
            double sy= sigma(wm.sy, test_point_source_local);
            double sz= sigma(wm.sz, test_point_source_local);

            double rate= source.s[3];
            double speed= meas.vel;

            double expy= std::exp((std::pow(-test_point_source_local.pos[1],2))/(2*std::pow(test_point_source_local.pos[1],2)));
            double expz= std::exp((std::pow(-test_point_source_local.pos[2],2))/(2*std::pow(test_point_source_local.pos[2],2)));
            double norm= ((rate/speed)/(2*M_PI*sy*sz));

            predicted_concentration[i]=norm*expy*expz;
        }
   }
   return;
}

std::vector<double> Predict::getPredictedConcentrations() {return predicted_concentration;}


double Predict::sigma(const double wm_i[3], const position& local_test_point)
{
    double x= local_test_point.pos[0]; //Source local downwind distance x
    return wm_i[0]*x*std::pow(1+wm_i[1]*x,-wm_i[2]);
}