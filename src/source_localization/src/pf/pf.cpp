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
    // https://stackoverflow.com/questions/30088025/malloc-invalid-conversion-from-void-to-double
    pf = new pf_t[sizeof(pf_t)];

    pf->min_samples = min_samples;
    pf->max_samples = max_samples;

    pf->current_set = 0;

    for (j = 0; j < 2; j++)
    {
        // Build set 1/2 first (set=0) then loop and build set 2/2 (set=1)
        set = pf->sets + j;
      
        set->sample_count = max_samples;
        // set->samples = (std::shared_ptr<pf_sample_t>) calloc(max_samples, sizeof(pf_sample_t));

        // for (i = 0; i < set->sample_count; i++)
        // {
        //     sample = set->samples + i;
        //     sample->state.v[0] = 0.0;
        //     sample->state.v[1] = 0.0;
        //     sample->state.v[2] = 0.0;
        //     sample->state.v[3] = 0.0;
        //     sample->weight = 1.0 / max_samples;
        // }
        set->mean = pf_vector_zero();
        set->cov = pf_matrix_zero();
    }

    return pf;
}