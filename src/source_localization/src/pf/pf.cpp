#include "cstdlib"
#include "iostream"

#include "../include/pf/pf.h"



// Create a new filter
std::shared_ptr<pf_t> pf_alloc(int min_samples, int max_samples)
{
    int i, j;
    // Are these the right type of pointers?
    std::shared_ptr<pf_t> pf;
    std::unique_ptr<pf_sample_set_t>* set;
    //pf_sample_t* sample;

    pf.reset(new pf_t());

    pf->min_samples = min_samples;
    pf->max_samples = max_samples;

    pf->current_set = 0;
    for (j = 0; j < 2; j++)
    {
      set = (pf->sets + j);
      set->reset(new pf_sample_set_t);
      (*set)->sample_count = max_samples;
      // Dynamically assigned array containing all samples (particles)
      // set->samples = (pf_sample_t*) new pf_sample_t[max_samples];

        // for (i = 0; i < set->sample_count; i++)
        // {
        //     sample = set->samples + i;
        //     sample->state.v[0] = i;
        //     sample->state.v[1] = 0.0;
        //     sample->state.v[2] = 0.0;
        //     sample->state.v[3] = 0.0;
        //     sample->weight = 1.0 / max_samples;
        // }

      (*set)->mean = pf_vector_zero();
      (*set)->cov = pf_matrix_zero();
    }
    

    // //set converged to 0
    // pf_init_converged(pf);

  return pf;
}