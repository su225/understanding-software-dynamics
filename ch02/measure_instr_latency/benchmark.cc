#include <cstdio>
#include <cstdint>

using namespace std;

#define MAX_ITERATIONS 100000000

int main() {
    int32_t sum = 0;
    for (int32_t i = 0; i < MAX_ITERATIONS; i++) {
        sum += 1;        
    }
    printf("sum = %d", sum);
    return 0;
}
