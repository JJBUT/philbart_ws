#include "predict.h"


#include "iostream"
Predict::Predict(const filter_state& filter, wind_model wm ):
    filter{filter},
    wm{wm}
{
    predicted_concentration.resize(filter.sets[0].particle_count);
}

Predict::~Predict(){}

void Predict::PredictConcentration(const measurement& meas, const position& test_point)
{
    //Questions: is the tf fn. a potential inline candidate?
    //For particle in set 0, 
        //Convert the test point into a particle local frame using the azimuth and position data
        //Calculate the concentration that we predict we should sense at our curerent location
}

std::vector<double> Predict::GetPredictedConcentrations() {return predicted_concentration;}