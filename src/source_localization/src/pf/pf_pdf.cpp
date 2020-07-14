#include "random"
#include "../include/pf/pf_pdf.h"

pf_vector_t pf_pdf_uniform_sample(x_min, x_max, y_min, y_max, z_min, zmax, rate_min, rate_max)
{
    // Random number engine for uniform distribution
    // Taken from code here https://stackoverflow.com/questions/18880654/why-do-i-get-the-same-sequence-for-every-run-with-stdrandom-device-with-mingw/18880689#18880689
    // Used ^^ to generate new seed everytime
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    pf_vector_t v;

    v[0]= _min +distribution(mt) *(_max-_min);
    v[1]= _min +distribution(mt) *(_max-_min);
    v[2]= _min +distribution(mt) *(_max-_min);
    v[3]= _min +distribution(mt) *(_max-_min);
    return v;
}
