#include "cstdlib"
#include "iostream"

#include "../include/pf/pf.h"



// Create a new filter
std::shared_ptr<pf_t> pf_alloc(int min_samples, int max_samples)
{
    int i, j;
    // Are these the right type of pointers?
    std::shared_ptr<pf_t> pf;
    pf_sample_set_t* set;
    std::unique_ptr<pf_sample_t> sample;

    pf.reset(new pf_t());

    pf->min_samples = min_samples;
    pf->max_samples = max_samples;

    pf->current_set = 0;
    for (j = 0; j < 2; j++)
    {
      set = pf->sets + j;
      
      set->sample_count = max_samples;
      //set->samples = calloc(max_samples, sizeof(pf_sample_t));

      // Start here to see how you can create an array with custom datatype
      //https://stackoverflow.com/questions/8579694/how-do-i-declare-an-array-with-a-custom-class

    //     for (i = 0; i < set->sample_count; i++)
    //     {
    //         sample = set->samples + i;
    //         sample->pose.v[0] = 0.0;
    //         sample->pose.v[1] = 0.0;
    //         sample->pose.v[2] = 0.0;
    //         sample->weight = 1.0 / max_samples;
    //     }

      set->mean = pf_vector_zero();
      set->cov = pf_matrix_zero();
    }

//   //set converged to 0
//   pf_init_converged(pf);

  return pf;
}