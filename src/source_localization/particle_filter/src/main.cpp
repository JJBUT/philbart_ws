#include "iostream"

#include "../include/initialize.h"
#include "../include/predict.h"
/*Development Notes
// Depending on how the ros implementation goes, I cna probably pass the wind model and state space via reference 
*/

int main()
{
    state_space ss(-10,10,-10,10,0,10,0,10000);
    int num_particles= 10;
    Initialize init_filter(num_particles, ss);
    std::unique_ptr<filter_state> fake_filter=init_filter.getFilter();

    wind_model wm(.1,.1,.1,.1,.1,.1);   
    Predict fake_predict(*fake_filter, wm);

    measurement meas(0.0,1.3,1.4,10050);
    position fake_test_point;
    fake_test_point.pos[0]=5.0;
    fake_test_point.pos[1]=0.0;
    fake_test_point.pos[2]=0.0;
    fake_predict.predictConcentration(meas, fake_test_point);

    std::vector<double> fake_predicted_concentration = fake_predict.getPredictedConcentrations();

   
    



}