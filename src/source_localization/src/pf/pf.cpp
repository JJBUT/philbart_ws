#include "cstdlib"
#include "iostream"
#include "random"

#include "../include/pf/pf.h"
#include "../include/pf/pf_pdf.h"




// Create a new filter
void pf_alloc(std::shared_ptr<pf_t>& pf, int min_samples, int max_samples)
{
    // The pf has two sets, each set has a couple thousand particles
    // This function is responsible for allocating the memory (with zeros)
    // that the pf will use. The memory values can be reassigned or set 
    // equal to zero but for the entire filter the memory addresses
    // should never actually change.

    int i, j;

    // Allocate and take ownership of the pf's memory
    pf.reset(new pf_t());  

    pf->min_samples = min_samples;
    pf->max_samples = max_samples;
    pf->current_set = 0;

    for (j = 0; j < 2; j++)
    {
      // Allocate the two k and k+1 sets  
      pf->sets[j].sample_count = max_samples;
      // Allocate the memory for the set's sample vector
      pf->sets[j].samples.reserve(max_samples);

      for (i = 0; i < pf->sets[j].sample_count; i++)
      {
        // Allocate each sets samples
        pf->sets[j].samples[i].state.v[0] = 0.0;
        pf->sets[j].samples[i].state.v[1] = 0.0;
        pf->sets[j].samples[i].state.v[2] = 0.0;
        pf->sets[j].samples[i].state.v[3] = 0.0;
        pf->sets[j].samples[i].weight = 1.0 / max_samples;
      }

       pf->sets[j].mean = pf_vector_zero();
       pf->sets[j].cov = pf_matrix_zero();
    }

  return;
}

void pf_init_uniform(std::shared_ptr<pf_t>  pf, std::shared_ptr<map_t> map,  double z_min, double z_max, double rate_min, double rate_max )
{
  // Future considerations: add tf ability to map if it has had a rotation 
  int i;

  double x_min= map->ros_map.info.origin.position.x - map->width/2.0; 
  double x_max= map->ros_map.info.origin.position.x + map->width/2.0;
  double y_min= map->ros_map.info.origin.position.y - map->height/2.0; 
  double y_max= map->ros_map.info.origin.position.y + map->height/2.0;
  
  
  for (i = 0; i < pf->sets[0].sample_count; i++)
  {
    // Iterate through the first set's samples and fill out their values with
    // uniformly distributed values within state space bounds
    pf->sets[0].samples[i].state= pf_pdf_uniform_sample(x_min, x_max, y_min, y_max, z_min, z_max, rate_min, rate_max);
  }

}