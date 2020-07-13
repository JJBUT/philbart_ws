#include "cstdlib"
#include "iostream"

#include "../include/pf/pf.h"



// Create a new filter
pf_t *pf_alloc(int min_samples, int max_samples)
{
    int i, j;
    // Are these the right type of pointers?
    pf_t *pf;
    pf_sample_set_t *set;
    pf_sample_t *sample;

    // Use new instead of calloc which is more common in C
    
    // pf = calloc(1, sizeof(pf_t));

    // pf->min_samples = min_samples;
    // pf->max_samples = max_samples;

    // pf->current_set = 0;
    // for (j = 0; j < 2; j++)
    // {
    //     set = pf->sets + j;
      
    //     set->sample_count = max_samples;
    //     set->samples = calloc(max_samples, sizeof(pf_sample_t));

    //     for (i = 0; i < set->sample_count; i++)
    //     {
    //         sample = set->samples + i;
    //         sample->pose.v[0] = 0.0;
    //         sample->pose.v[1] = 0.0;
    //         sample->pose.v[2] = 0.0;
    //         sample->weight = 1.0 / max_samples;
    //     }

    //     set->mean = pf_vector_zero();
    //     set->cov = pf_matrix_zero();
    // }

//   //set converged to 0
//   pf_init_converged(pf);

  return pf;
}