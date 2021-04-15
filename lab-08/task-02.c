#include <omp.h>
#include <stdio.h>

int main() {
    double sum = 0;
    int const n = 10000;
    double s = omp_get_wtime();
#pragma omp parallel for
    for (int i = 1; i <= n; ++i) {
        sum += 1 / (double) i;
    }
#pragma omp barrier
    double e = omp_get_wtime();
    printf("Sum: %lf\n", sum);
    FILE *file = fopen("log.txt", "a");
    fprintf(file, "Sum of harmonic series till %d calculated in %lf\n", n,
            e - s);
}