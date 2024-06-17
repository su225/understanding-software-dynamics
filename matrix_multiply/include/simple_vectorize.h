#include <sys/types.h>

double matrix_multiply_vectorized_ikj(double *const restrict a, 
                                      double *const restrict b,
                                      double *restrict c,
                                      size_t n);

double matrix_multiply_vectorized_kij(double *const restrict a, 
                                      double *const restrict b,
                                      double *restrict c,
                                      size_t n);