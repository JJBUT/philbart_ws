#include "iostream"

#include "../include/initialize.h"
#include "../include/predict.h"


int main()
{
    state_space fake_ss;
    fake_ss.x[0]=-10.0;
    fake_ss.y[0]=-10.0;
    fake_ss.z[0]=-10.0;
    fake_ss.rate[0]=0.0;
    fake_ss.x[1]=10.0;
    fake_ss.y[1]=10.0;
    fake_ss.z[1]=10.0;
    fake_ss.rate[1]=1000.0;
    int fake_particle_count = 400;
    Initialize test(fake_particle_count, fake_ss );

    std::unique_ptr<filter_state> fake_filter = test.GetFilter();

    wind_model fake_wind_model;
    measurement fake_measurement;
    Predict fake_predict(fake_wind_model, fake_measurement, *fake_filter);


}