#include "../include/plume/prediction.h"


std::shared_ptr<prediction_set> prediction_alloc(std::shared_ptr<pf_t> pf)
{
    int i, j, k;

    std::shared_ptr<prediction_set> ps;

    ps.reset(new prediction_set());

    ps->predictions = std::unique_ptr<prediction[]> (new prediction[pf->max_samples]);  // Allocate the memory for the samples


      for (i = 0; i < pf->max_samples; i++)
      {
        ps->predictions[i].source_state=&pf->sets[0].samples[i].state;
        ps->predictions[i].predicted_concentration=0.0;
      }

    return ps;
}