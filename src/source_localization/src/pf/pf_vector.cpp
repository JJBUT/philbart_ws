#include "math.h"

#include "../include/pf/pf_vector.h"

// Return a zero vector
pf_vector_t pf_vector_zero()
{
  pf_vector_t c;

  c.v[0] = 0.0;
  c.v[1] = 0.0;
  c.v[2] = 0.0;
  
  return c;
}

// Check for NAN or INF in any component
int pf_vector_finite(pf_vector_t a)
{
  int i;
  
  for (i = 0; i < 3; i++)
    if (!isfinite(a.v[i]))
      return 0;
  
  return 1;
}

// Simple vector addition
pf_vector_t pf_vector_add(pf_vector_t a, pf_vector_t b)
{
  pf_vector_t c;

  c.v[0] = a.v[0] + b.v[0];
  c.v[1] = a.v[1] + b.v[1];
  c.v[2] = a.v[2] + b.v[2];
  
  return c;
}

// Simple vector subtraction
pf_vector_t pf_vector_sub(pf_vector_t a, pf_vector_t b)
{
  pf_vector_t c;

  c.v[0] = a.v[0] - b.v[0];
  c.v[1] = a.v[1] - b.v[1];
  c.v[2] = a.v[2] - b.v[2];
  
  return c;
}

// Transform from local to global coords (a + b)


// Transform from global to local coords (a - b)

// Return a zero matrix
pf_matrix_t pf_matrix_zero()
{
  int i, j;
  pf_matrix_t c;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      c.m[i][j] = 0.0;
        
  return c;
}

// Check for NAN or INF in any component
int pf_matrix_finite(pf_matrix_t a)
{
  int i, j;
  
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      if (!isfinite(a.m[i][j]))
        return 0;
  
  return 1;
}
