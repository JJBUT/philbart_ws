#ifndef PREDICT_H
#define PREDICT_H

//stl
#include "memory"

//custom
#include "utils.h"

class Predict
{
//Classes are private by default :)
    const filter_state& filter; //By being  a referencce is the filter autmatically updated?
    wind_model wm;

    std::vector<double> predicted_concentration;

public:
    //If you want the function to use the pointee, pass a reference to it. 
    // There's no reason to tie the function to work only with some kind of smart pointer
    Predict(const filter_state& filt, wind_model wm );
    ~Predict();

    void PredictConcentration(const measurement& meas, const position& test_point);
    std::vector<double> GetPredictedConcentrations();
};



#endif