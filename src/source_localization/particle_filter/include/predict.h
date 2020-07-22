#ifndef PREDICT_H
#define PREDICT_H

//stl
#include "memory"

//custom
#include "utils.h"

class Predict
{
    const filter_state& filter; 
    wind_model wm;

    std::vector<double> predicted_concentration;
    
    // Calculate the vertical and horizontal dispersion as a function of downwind distance
    double sigma(const double wm_i[3], const position& local_test_point);

public:
    Predict(const filter_state& filt, wind_model wm );
    ~Predict();

    // Calculate the individually concentration the GP model predicts at some test point from each particle
    void predictConcentration(const measurement& meas, const position& test_point);
    // Get the predicted concentration
    std::vector<double> getPredictedConcentrations();
};



#endif