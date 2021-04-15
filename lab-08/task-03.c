#include <omp.h>
#include <stdio.h>

#define R 5
#define C 5

void print(int matrix[R][C]) {
    for (int i = 0; i < R; ++i) {
        printf("[ ");
        for (int j = 0; j < C; ++j) {
            printf("%3d ", matrix[i][j]);
        }
        puts(" ]");
    }
    puts("");
}

int main() {
    int a[R][C], b[R][C], c[R][C];
    int k = 0;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            a[i][j] = k++;
        }
    }
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            b[i][j] = k--;
        }
    }
    omp_set_num_threads(C);
    double s = omp_get_wtime();
    for (int i = 0; i < R; ++i) {
#pragma omp parallel for
        for (int j = 0; j < C; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
#pragma omp barrier
    double e = omp_get_wtime();
    print(a);
    print(b);
    print(c);
    FILE *file = fopen("log.txt", "a");
    fprintf(file, "Matrix summation (%d x %d) done in %lf seconds\n", R, C,
            e - s);
}