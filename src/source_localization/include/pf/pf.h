#ifndef PF_H
#define PF_H


#include "memory" //smart pointers
#include "../include/pf/pf_vector.h"


// Function prototype for the initialization model; generates a sample pose from
// an appropriate distribution.
typedef pf_vector_t (*pf_init_model_fn_t) (void *init_data);


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
  std::shared_ptr<pf_sample_t> samples;

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
  pf_sample_set_t sets[2];

  int converged; 

} pf_t;


// Create a new filter
pf_t *pf_alloc(int min_samples, int max_samples, pf_init_model_fn_t random_pose_fn, void *random_pose_data);


#endif