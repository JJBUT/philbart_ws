#ifndef PF_VECTOR_H
#define PF_VECTOR_H


// The basic vector
// Sized to store the four member state
typedef struct
{
  double v[4];
} pf_vector_t;

// The basic matrix
// Sized to store the covariance of the four member state
typedef struct
{
  double m[4][4];
} pf_matrix_t;

// Return a zero vector
pf_vector_t pf_vector_zero();

// Check for NAN or INF in any component
int pf_vector_finite(pf_vector_t a);

// Simple vector addition
pf_vector_t pf_vector_add(pf_vector_t a, pf_vector_t b);

// Simple vector subtraction
pf_vector_t pf_vector_sub(pf_vector_t a, pf_vector_t b);

// Transform from local to global coords (a + b)


// Transform from global to local coords (a - b)

// Return a zero matrix
pf_matrix_t pf_matrix_zero();

// Check for NAN or INF in any component
int pf_matrix_finite(pf_matrix_t a);


#endif