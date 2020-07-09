#include "iostream"
#include "../include/sensors/sl_anemometer.h"

void trial();

int main(){
    //sensor_trial();
    trial();
    return 0;
}

void trial()
{
    // Goal for July 9 2020 9:33AM:
    // Troubleshoot SLAnemometer and SLAnemometerData
    // See that the sensor can just be created once and the data updated continously
    // Built out the Anemometer function implementations in sl_anemometer.cpp

    //Build up ros infrastructure to more fully understand requirements of classes
    sl::SLAnemometer sensor1;
    sl::SLAnemometerData sensor1_data; 
    
}