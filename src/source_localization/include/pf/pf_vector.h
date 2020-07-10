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
