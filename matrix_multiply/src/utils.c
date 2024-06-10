#include <stdio.h>

const char* humanize_floating_point_ops(double ops, double elapsed_time) {
    double flops = ops / elapsed_time;
    const char* units[] = {"", "K", "M", "G", "T", "P"};
    int unit_index = 0;
    
    while (flops >= 1000 && unit_index < 5) {
        flops /= 1000;
        unit_index++;
    }
    
    static char result[20]; // Assuming the result won't exceed 20 characters
    sprintf(result, "%.2f %sFLOPS", flops, units[unit_index]);
    
    return result;
}
