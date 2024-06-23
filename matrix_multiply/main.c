#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdalign.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <arm_neon.h>

#include <mach/mach.h>
#include <mach/thread_policy.h>

#include "simple.h"
#include "simple_vectorize.h"
#include "utils.h"
#include "transpose.h"
#include "block.h"
#include "block_vectorize.h"

#define N          2048
#define PAGE_ALIGN 16384

/// @brief compute sum of all matrix elements
/// @param a input matrix of size N*N
/// @return scalar of the sum of all elements
double matrix_element_sum(double *const restrict a) {
    double sum = 0.0;
    for (int i = 0; i < N*N; i+=2) {
        float64x2_t data = vld1q_f64(&a[i]);
        float64x2_t sum_vec = vpaddq_f64(data, data);
        sum += vgetq_lane_f64(sum_vec, 0);
        sum += vgetq_lane_f64(sum_vec, 1);
    }
    return sum;
}

alignas(PAGE_ALIGN) double a[N*N], b[N*N];
alignas(PAGE_ALIGN) double c[N*N];

int main(int argc, char *argv[]) {
    integer_t cpu_id = 0;
    thread_port_t mach_thread = mach_thread_self();
    thread_affinity_policy_data_t policy = {.affinity_tag = cpu_id};
    thread_policy_set(mach_thread, THREAD_AFFINITY_POLICY, (thread_policy_t)&policy, 1);

    srand(time(0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i*N + j] = 1.0 + ((double)i / N);
            b[i*N + j] = 1.0 + ((double)j / N);
        }
    }
    memset(c, 0, N*N);
    double elapsed_time;

    printf("=== ALGORITHM: %s ===\n", argv[1]);
    if (strcmp(argv[1], "--simple-ijk") == 0) {
        elapsed_time = matrix_multiply_simple_ijk(a, b, c, N);
    } else if (strcmp(argv[1], "--simple-ikj") == 0) {
        elapsed_time = matrix_multiply_simple_ikj(a, b, c, N);
    } else if (strcmp(argv[1], "--simple-jik") == 0) {
        elapsed_time = matrix_multiply_simple_jik(a, b, c, N);
    } else if (strcmp(argv[1], "--simple-jki") == 0) {
        elapsed_time = matrix_multiply_simple_jki(a, b, c, N);
    } else if (strcmp(argv[1], "--simple-kij") == 0) {
        elapsed_time = matrix_multiply_simple_kij(a, b, c, N);
    } else if (strcmp(argv[1], "--simple-kji") == 0) {
        elapsed_time = matrix_multiply_simple_kji(a, b, c, N);
    } else if (strcmp(argv[1], "--vec-ikj") == 0) {
        elapsed_time = matrix_multiply_vectorized_ikj(a, b, c, N);
    } else if (strcmp(argv[1], "--vec-kij") == 0) {
        elapsed_time = matrix_multiply_vectorized_kij(a, b, c, N);
    } else if (strcmp(argv[1], "--block") == 0) {
        // format --block --<ijk|ikj|..> --block_size <blksz> --vec
        //        1       2              3            4       5
        if (argc != 5 && argc != 6) {
            printf("expected block size to be provided when using block\n");
            return -1;
        }
        bool vectorize = argc == 6;
        size_t block_size = strtoul(argv[4], NULL, 10);
        if (block_size == 0) {
            printf("block_size must be specified as a number: eg: --block-size 16\n");
            return -1;
        }
        if (block_size >= N) {
            block_size = N;
        }
        if ((block_size & (block_size-1)) != 0) {
            printf("block_size must be a power of 2\n");
            return -1;
        }
        if (vectorize) {
            printf("\t==== traversal = %s | block_size = %zu | vectorize ====\n", argv[2], block_size);
            if (strcmp(argv[2], "--ikj") == 0) {
                elapsed_time = matrix_multiply_blockvec_ikj(a, b, c, N, block_size);
            }
        } else {
            printf("\t==== traversal = %s | block_size = %zu ====\n", argv[2], block_size);
            if (strcmp(argv[2], "--ijk") == 0) {
                elapsed_time = matrix_multiply_block_ijk(a, b, c, N, block_size);   
            } else if (strcmp(argv[2], "--ikj") == 0) {
                elapsed_time = matrix_multiply_block_ikj(a, b, c, N, block_size);
            }
        }
    } else {
        printf("unknown algorithm: %s\n", argv[1]);
        return -1;
    }

    double actual_matrix_sum = matrix_element_sum(c);
    printf("\telapsed time                 =  %.3f secs\n", elapsed_time);
    printf("\tFLOPS                        =  %s\n", humanize_floating_point_ops(2.0*N*N*N, elapsed_time));

    double diff = 38642123776 - actual_matrix_sum;
    if (fabs(diff) > 1e-6) {
        printf("<<<< INCORRECT IMPLEMENTATION >>>>\n");
        printf("\tactual product matrix sum    =  %f\n", actual_matrix_sum);
        printf("\texpected product matrix sum  =  %f\n", 38642123776.0);
        printf("\tdifference                   =  %f\n", diff);
    }
    return 0;
}