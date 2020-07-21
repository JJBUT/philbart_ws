#ifndef PREDICT_H
#define PREDICT_H

//stl
#include "memory"

//custom
#include "utils.h"

class Predict
{
    /*data*/
public:
    //If you want the function to use the pointee, pass a reference to it. 
    // There's no reason to tie the function to work only with some kind of smart pointer
    Predict(wind_model wm, measurement meas, const filter_state& filter);
    ~Predict();
};



#endif