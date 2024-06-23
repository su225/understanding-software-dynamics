#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

double matrix_multiply_block_ijk(double *const restrict a, 
                                 double *const restrict b,
                                 double *restrict c,
                                 size_t n, size_t block_size) {
    if (n % block_size != 0) {
        printf("block size must divide n exactly\n");
        exit(-1);
    }
    
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    size_t num_blocks = n / block_size;
    for (int bi = 0; bi < num_blocks; bi++) {
        for (int bj = 0; bj < num_blocks; bj++) {
            for (int bk = 0; bk < num_blocks; bk++) {
                for (int i = 0; i < block_size; i++) {
                    for (int j = 0; j < block_size; j++) {
                        for (int k = 0; k < block_size; k++) {
                            size_t ii = bi * block_size + i;
                            size_t jj = bj * block_size + j;
                            size_t kk = bk * block_size + k;
                            c[ii*n + jj] += a[ii*n + kk] * b[kk*n + jj];
                        }
                    }
                }
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time_secs = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return elapsed_time_secs;
}

double matrix_multiply_block_ikj(double *const restrict a, 
                                 double *const restrict b,
                                 double *restrict c,
                                 size_t n, size_t block_size) {
    if (n % block_size != 0) {
        printf("block size must divide n exactly\n");
        exit(-1);
    }
    
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    size_t num_blocks = n / block_size;
    for (int bi = 0; bi < num_blocks; bi++) {
        for (int bk = 0; bk < num_blocks; bk++) {
            for (int bj = 0; bj < num_blocks; bj++) {
                for (int i = 0; i < block_size; i++) {
                    for (int k = 0; k < block_size; k++) {
                        for (int j = 0; j < block_size; j++) {
                            size_t ii = bi * block_size + i;
                            size_t jj = bj * block_size + j;
                            size_t kk = bk * block_size + k;
                            c[ii*n + jj] += a[ii*n + kk] * b[kk*n + jj];
                        }
                    }
                }
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time_secs = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return elapsed_time_secs;
}
