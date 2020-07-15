#include "random"
#include "../include/pf/pf_pdf.h"

pf_vector_t pf_pdf_uniform_sample(double x_min, double x_max, double y_min, double y_max, double z_min, double z_max, double rate_min, double rate_max)
{
    // Random number engine for uniform distribution
    // Taken from code here https://stackoverflow.com/questions/18880654/why-do-i-get-the-same-sequence-for-every-run-with-stdrandom-device-with-mingw/18880689#18880689
    // Used ^^ to generate new seed everytime
    pf_vector_t vec;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    vec.v[0]= x_min + distribution(mt) * (x_max - x_min);
    vec.v[1]= y_min + distribution(mt) * (y_max - y_min);
    vec.v[2]= z_min + distribution(mt) * (z_max - z_min);
    vec.v[3]= rate_min + distribution(mt) * (rate_max - rate_min);

    return vec;
}
