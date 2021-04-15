#include <math.h>
#include <omp.h>
#include <stdio.h>

int main() {
    double const a = 0, x = 3;
    double taylor = 0;
    unsigned long long fact = 1;
#pragma omp parallel for
    for (int n = 1; n < 21; ++n) {
        taylor += exp(a) * pow(x - a, n) / (long double) fact;
        fact *= n;
    }
#pragma omp barrier
    printf("Taylor sum: %lf\n", taylor);
}