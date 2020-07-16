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

namespace sl
{

typedef struct 
{
    double sy[3];
    double sz[3];
} wind_model;

typedef struct
{
    //store the address of the sample
    //Store the predicted concentration produced by that sample
    
} prediction;






}

#endif