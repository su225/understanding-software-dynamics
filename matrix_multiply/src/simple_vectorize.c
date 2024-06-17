#include <sys/types.h>
#include <arm_neon.h>
#include <stdlib.h>
#include <time.h>

double matrix_multiply_vectorized_ikj(double *const restrict a, 
                                      double *const restrict b,
                                      double *restrict c,
                                      size_t n) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < n; i++) {
        size_t in = i*n;
        for (int k = 0; k < n; k++) {
            size_t kn = k*n;
            float64x2_t aik = vdupq_n_f64(a[in + k]);
            for (int j = 0; j < n; j+=2) {
                float64x2_t cij = vld1q_f64(&c[in + j]);
                float64x2_t bkj = vld1q_f64(&b[kn + j]);
                cij = vfmaq_f64(cij, aik, bkj);
                vst1q_f64(&c[in + j], cij);
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time_secs = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return elapsed_time_secs;
}

double matrix_multiply_vectorized_kij(double *const restrict a, 
                                      double *const restrict b,
                                      double *restrict c,
                                      size_t n) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int k = 0; k < n; k++) {
        size_t kn = k*n;
        for (int i = 0; i < n; i++) {
            size_t in = i*n;
            float64x2_t aik = vdupq_n_f64(a[in + k]);
            for (int j = 0; j < n; j+=2) {
                float64x2_t cij = vld1q_f64(&c[in + j]);
                float64x2_t bkj = vld1q_f64(&b[kn + j]);
                cij = vfmaq_f64(cij, aik, bkj);
                vst1q_f64(&c[in + j], cij);
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time_secs = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return elapsed_time_secs;
}