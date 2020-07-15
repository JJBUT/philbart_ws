#ifndef PF_PDF_H
#define PF_PDF_H


#include "../include/pf/pf_vector.h"

pf_vector_t pf_pdf_uniform_sample(double x_min, double x_max, double y_min, double y_max, double z_min, double z_max, double rate_min, double rate_max);


#endif