#include <arm_neon.h>
// The 2x2 matrix consisting of 4 elements looks like
// this when stored in the row-major order.
// | 0 1 |
// | 2 3 |
//
// Hence, for computing the transpose, we have to swap
// elements 1 and 2. That's all.

inline void swap_double(double *restrict a,
                        double *restrict b);
    
void transpose_2x2_naive(double *restrict a) {
    swap_double(&a[1], &a[2]);
}

void transpose_2x2_arm_neon_simd(double *restrict a) {
    float64x2_t r1 = vld1q_f64(a);
    float64x2_t r2 = vld1q_f64(a+2);
    float64x2_t t1 = vtrn1q_f64(r1, r2);
    float64x2_t t2 = vtrn2q_f64(r1, r2);
    vst1q_f64(a, t1);
    vst1q_f64(a+2, t2);
}

inline void swap_double(double *restrict a,
                        double *restrict b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}
