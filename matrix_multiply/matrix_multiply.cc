#include "performancecounters/event_counter.h"

#define MATRIX_SIZE 1024

event_aggregate matrix_multiply_naive_col_by_row(double a[][MATRIX_SIZE],
                                                 double b[][MATRIX_SIZE],
                                                 double c[][MATRIX_SIZE]) {

}

event_aggregate matrix_multiply_naive_row_by_col(double a[][MATRIX_SIZE],
                                                 double b[][MATRIX_SIZE],
                                                 double c[][MATRIX_SIZE]) {

}

event_aggregate matrix_multiply_transpose_inplace_scalar(double a[][MATRIX_SIZE],
                                                         double b[][MATRIX_SIZE],
                                                         double c[][MATRIX_SIZE]) {

}

event_aggregate matrix_multiply_transpose_inplace_neon(double a[][MATRIX_SIZE],
                                                       double b[][MATRIX_SIZE],
                                                       double c[][MATRIX_SIZE]) {
    
}

event_aggregate matrix_multiply_block_scalar(double a[][MATRIX_SIZE],
                                             double b[][MATRIX_SIZE],
                                             double c[][MATRIX_SIZE]) {

}

event_aggregate matrix_multiply_block_neon(double a[][MATRIX_SIZE],
                                           double b[][MATRIX_SIZE],
                                           double c[][MATRIX_SIZE]) {

}

int main() {
    double a[MATRIX_SIZE][MATRIX_SIZE];
    double b[MATRIX_SIZE][MATRIX_SIZE];
    double c[MATRIX_SIZE][MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            a[i][j] = 1.0 + (static_cast<double>(i) / static_cast<double>(MATRIX_SIZE-1));
            b[i][j] = 1.0 + (static_cast<double>(j) / static_cast<double>(MATRIX_SIZE-1));
        }
    }
    return 0;
}