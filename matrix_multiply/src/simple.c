#include <stdlib.h>
#include <time.h>

double matrix_multiply_simple_ijk(double *const restrict a, 
                                  double *const restrict b,
                                  double *restrict c,
                                  size_t n) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[i*n + j] += (a[i*n + k] * b[k*n + j]);
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time_secs = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return elapsed_time_secs;
}

double matrix_multiply_simple_ikj(double *const restrict a, 
                                  double *const restrict b,
                                  double *restrict c,
                                  size_t n) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                c[i*n + j] += (a[i*n + k] * b[k*n + j]);
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time_secs = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return elapsed_time_secs;
}

double matrix_multiply_simple_jik(double *const restrict a, 
                                  double *const restrict b,
                                  double *restrict c,
                                  size_t n) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                c[i*n + j] += (a[i*n + k] * b[k*n + j]);
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time_secs = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return elapsed_time_secs;
}

double matrix_multiply_simple_jki(double *const restrict a, 
                                  double *const restrict b,
                                  double *restrict c,
                                  size_t n) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                c[i*n + j] += (a[i*n + k] * b[k*n + j]);
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time_secs = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return elapsed_time_secs;
}

double matrix_multiply_simple_kij(double *const restrict a, 
                                  double *const restrict b,
                                  double *restrict c,
                                  size_t n) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                c[i*n + j] += (a[i*n + k] * b[k*n + j]);
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time_secs = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return elapsed_time_secs;
}

double matrix_multiply_simple_kji(double *const restrict a, 
                                  double *const restrict b,
                                  double *restrict c,
                                  size_t n) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (int k = 0; k < n; k++) {
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n; i++) {
                c[i*n + j] += (a[i*n + k] * b[k*n + j]);
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time_secs = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    return elapsed_time_secs;
}
