#include "performancecounters/event_counter.h"

#define MATRIX_SIZE 1024

#ifndef PAGE_ALIGN
#define PAGE_ALIGN 16384 // Page size in M3 is 16KB
#endif

event_aggregate matrix_multiply_naive_row_by_col(const double **__restrict a,
                                                 const double **__restrict b,
                                                 double **__restrict c) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            c[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                c[i][j] += (a[i][k] * b[k][j]);
            }
        }
    }
}

event_aggregate matrix_multiply_naive_col_by_row(const double *__restrict a,
                                                 const double *__restrict b,
                                                 double *__restrict c) {

}

event_aggregate matrix_multiply_transpose_inplace_scalar(const double *__restrict a,
                                                         const double *__restrict b,
                                                         double *__restrict c) {

}

event_aggregate matrix_multiply_transpose_inplace_neon(const double *__restrict a,
                                                       const double *__restrict b,
                                                       double *__restrict c) {
    
}

event_aggregate matrix_multiply_block_scalar(const double *__restrict a,
                                             const double *__restrict b,
                                             double *__restrict c) {

}

event_aggregate matrix_multiply_block_neon(const double *__restrict a,
                                           const double *__restrict b,
                                           double *__restrict c) {
                                        
}

int main() {
    double alignas(PAGE_ALIGN) a[MATRIX_SIZE][MATRIX_SIZE];
    double alignas(PAGE_ALIGN) b[MATRIX_SIZE][MATRIX_SIZE];
    double alignas(PAGE_ALIGN) c[MATRIX_SIZE][MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            a[i][j] = 1.0 + (static_cast<double>(i) / static_cast<double>(MATRIX_SIZE-1));
            b[i][j] = 1.0 + (static_cast<double>(j) / static_cast<double>(MATRIX_SIZE-1));
        }
    }
    return 0;
}