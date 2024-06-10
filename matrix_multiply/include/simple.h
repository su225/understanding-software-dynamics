#ifndef __MATRIX_MUL_SIMPLE_ALGORITHMS_H
#define __MATRIX_MUL_SIMPLE_ALGORITHMS_H

#include <sys/types.h>

/// @brief 
///     multiplies two square matrices of size N*N namely a and b
///     and stores the result in c and returns the time elapsed. 
/// @param a input matrix 2 (square matrix of size N)
/// @param b input matrix 2 (square matrix of size N)
/// @param c resulting matrix (assume sufficient memory is allocated)
/// @return time in seconds elapsed for matrix multiplication
double matrix_multiply_simple_ijk(double *const restrict a, 
                                  double *const restrict b,
                                  double *restrict c,
                                  size_t n);

double matrix_multiply_simple_ikj(double *const restrict a, 
                                  double *const restrict b,
                                  double *restrict c,
                                  size_t n);

double matrix_multiply_simple_jik(double *const restrict a, 
                                  double *const restrict b,
                                  double *restrict c,
                                  size_t n);

double matrix_multiply_simple_jki(double *const restrict a, 
                                  double *const restrict b,
                                  double *restrict c,
                                  size_t n);

double matrix_multiply_simple_kij(double *const restrict a, 
                                  double *const restrict b,
                                  double *restrict c,
                                  size_t n);

double matrix_multiply_simple_kji(double *const restrict a, 
                                  double *const restrict b,
                                  double *restrict c,
                                  size_t n);

#endif