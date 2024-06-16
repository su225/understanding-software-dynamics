#include <stdio.h>
#include <arm_neon.h>

void swap_double(double *restrict a,
                 double *restrict b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

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

int main(void) {
    double matrix1[4] = {0, 1, 2, 3};
    double matrix2[4] = {0, 1, 2, 3};
    transpose_2x2_naive(matrix1);
    transpose_2x2_arm_neon_simd(matrix2);

    printf("%lf %lf %lf %lf\n", matrix1[0], matrix1[1], matrix1[2], matrix1[3]);
    printf("%lf %lf %lf %lf\n", matrix2[0], matrix2[1], matrix2[2], matrix2[3]);
    return 0;
}
