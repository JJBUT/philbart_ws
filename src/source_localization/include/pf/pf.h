#ifndef PF_H
#define PF_H


#include "memory" //smart pointers
#include "../include/pf/pf_vector.h"
#include "../include/map/map.h"


// Information for a single sample
typedef struct
{
  // State represented by a sample
  // (x, y, z, q)
  // Source position and emission rate
  pf_vector_t state;

  // Weight for this state
  double weight;
  
} pf_sample_t;



// Information for a set of samples
// Each filter has two sets of samples; the last time step and the current time step
typedef struct
{
  // The samples
  int sample_count;
  //pf_sample_t * samples;
  std::unique_ptr<pf_sample_t[]> samples;

  // Filter statistics
  pf_vector_t mean;
  pf_matrix_t cov;
  int converged; 
  double n_eff;

} pf_sample_set_t;



// Information for the entire filter
typedef struct
{
  // This min and max number of samples
  int min_samples, max_samples;

  // The sample sets.  We keep two sets and use [current_set]
  // to identify the active set.
  int current_set;
  //pf_sample_set_t sets[2];
  std::unique_ptr< pf_sample_set_t> sets[2];

  int converged; 

} pf_t;


// Create a new filter
std::shared_ptr<pf_t> pf_alloc(int min_samples, int max_samples);

// Initialize the filter with a uniform distribution
void pf_init(std::shared_ptr<pf_t>  pf, std::shared_ptr<map_t> map);


#endif