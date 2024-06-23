#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <arm_neon.h>

double matrix_multiply_blockvec_ikj(double *const restrict a, 
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
                    size_t ii = bi * block_size + i;
                    for (int k = 0; k < block_size; k++) {
                        size_t kk = bk * block_size + k;
                        float64x2_t aik = vdupq_n_f64(a[ii*n + k]);
                        for (int j = 0; j < block_size; j+=2) {
                            size_t jj = bj * block_size + j;
                            float64x2_t cij = vld1q_f64(&c[ii*n + j]);
                            float64x2_t bkj = vld1q_f64(&b[kk*n + j]);
                            cij = vfmaq_f64(cij, aik, bkj);
                            vst1q_f64(&c[ii*n + j], cij);
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