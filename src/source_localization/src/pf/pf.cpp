#include "cstdlib"
#include "iostream"

#include "../include/pf/pf.h"



// Create a new filter
std::shared_ptr<pf_t> pf_alloc(int min_samples, int max_samples)
{
    // The pf has two sets, each set has a couple thousand particles
    // This function is responsible for allocating the memory (with zeros)
    // that the pf will use. The memory values can be reassigned or set 
    // equal to zero but for the entire filter the memory addresses
    // should never actually change.

    int i, j;
    // The particle filter being instantiated
    std::shared_ptr<pf_t> pf;
    // A recyclable set structure used to assigned in succession to the pf's two sets
    std::unique_ptr<pf_sample_set_t>* set;
    // A recyclable sample structure used to fill out the set's thousands of samples
    pf_sample_t* sample;

    pf.reset(new pf_t());  //Allocate the memory for the pf
    pf->min_samples = min_samples;
    pf->max_samples = max_samples;
    pf->current_set = 0;

    for (j = 0; j < 2; j++)
    {
      set = (pf->sets + j);
      set->reset(new pf_sample_set_t);  // Allocate the memory for the set
      (*set)->sample_count = max_samples;
      (*set)->samples = std::unique_ptr<pf_sample_t[]> (new pf_sample_t[max_samples]);  // Allocate the memory for the samples

      for (i = 0; i < (*set)->sample_count; i++)
      {
        sample = &((*set)->samples[i]); // Iterate through the samples and fill out their values
        sample->state.v[0] = 0.0;
        sample->state.v[1] = 0.0;
        sample->state.v[2] = 0.0;
        sample->state.v[3] = 0.0;
        sample->weight = 1.0 / max_samples;
      }

      (*set)->mean = pf_vector_zero();
      (*set)->cov = pf_matrix_zero();
    }
    
  return pf;
}