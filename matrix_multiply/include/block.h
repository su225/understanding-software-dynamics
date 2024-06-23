#ifndef __MATRIX_MUL_BLOCK_ALGORITHMS_H
#define __MATRIX_MUL_BLOCK_ALGORITHMS_H

#include <sys/types.h>

double matrix_multiply_block_ijk(double *const restrict a, 
                                 double *const restrict b,
                                 double *restrict c,
                                 size_t n, size_t block_size);

double matrix_multiply_block_ikj(double *const restrict a, 
                                 double *const restrict b,
                                 double *restrict c,
                                 size_t n, size_t block_size);

#endif