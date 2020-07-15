#include "cstdlib"
#include "iostream"
#include "random"

#include "../include/pf/pf.h"
#include "../include/pf/pf_pdf.h"




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
    pf_sample_set_t* set;
    // A recyclable sample structure used to fill out the set's thousands of samples
    pf_sample_t* sample;

    pf.reset(new pf_t());  //Allocate the memory for the pf
    pf->min_samples = min_samples;
    pf->max_samples = max_samples;

    pf->current_set = 0;
    for (j = 0; j < 2; j++)
    {
      set = pf->sets + j;
  
      set->sample_count = max_samples;
      set->samples = std::unique_ptr<pf_sample_t[]> (new pf_sample_t[max_samples]);  // Allocate the memory for the samples

      for (i = 0; i < set->sample_count; i++)
      {
        sample = &set->samples[i]; // Iterate through the samples and fill out their values
        sample->state.v[0] = 0.0;
        sample->state.v[1] = 0.0;
        sample->state.v[2] = 0.0;
        sample->state.v[3] = 0.0;
        sample->weight = 1.0 / max_samples;
      }

        set->mean = pf_vector_zero();
        set->cov = pf_matrix_zero();
    }

  return pf;
}

// void pf_init_uniform(std::shared_ptr<pf_t>  pf, std::shared_ptr<map_t> map,  double z_min, double z_max, double rate_min, double rate_max )
// {
//   // Future considerations: add tf ability to map if it had rotation 
//   int i, j;
//   std::unique_ptr<pf_sample_set_t>* set;
//   pf_sample_t* sample;

//   double x_min= map->ros_map.info.origin.position.x - map->width/2.0 ; double x_max= map->ros_map.info.origin.position.x + map->width/2.0 ;
//   double y_min= map->ros_map.info.origin.position.y - map->height/2.0 ; double y_max= map->ros_map.info.origin.position.y + map->height/2.0 ;
  
//   set = &(pf->sets[0]);
//   for (i = 0; i < (*set)->sample_count; i++)
//   {
//     // Iterate through the samples and fill out their values with uniform dist values within state space bounds
//     sample= &((*set)->samples[i]); 
//     sample->state= pf_pdf_uniform_sample(x_min, x_max, y_min, y_max, z_min, z_max, rate_min, rate_max);
//   }

// }