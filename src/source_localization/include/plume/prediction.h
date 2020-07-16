#ifndef PLUME_H
#define PLUME_H

#include "memory"

#include "../include/pf/pf.h"

/* Brain Storm July 16 2020
// We are going to need methods that calculate the expected concentration at a given
// point due to each individual particle
// We will need to store that predicted concentration
// We should have a pointer to the pf_ sets
*/


typedef struct 
{
    double sy[3];
    double sz[3];
} wind_model;

typedef struct
{
    //The source position (i.e. the particle state)
    pf_vector_t *source_state;
    //Store the predicted concentration produced by that sample
    double predicted_concentration;
    
} prediction;

typedef struct
{
    // The sensor position
    pf_vector_t test_point;
    // The array pf all calculated predictions for every particle
    std::unique_ptr<prediction[]> predictions;

} prediction_set;




std::shared_ptr<prediction_set> prediction_alloc(std::shared_ptr<pf_t> pf);





#endif