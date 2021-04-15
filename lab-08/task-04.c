#include <omp.h>
#include <stdio.h>

#define R 3
#define C 3

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
    int a[R][C], b[C][R], c[R][C] = {0};
    int k = 0;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            a[i][j] = k++;
        }
    }
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < R; ++j) {
            b[i][j] = k--;
        }
    }
    omp_set_num_threads(C);
    double s = omp_get_wtime();
    for (int i = 0; i < R; ++i) {
#pragma omp parallel for
        for (int j = 0; j < C; ++j) {
            for (int k = 0; k < C; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
#pragma omp barrier
    double e = omp_get_wtime();
    print(a);
    print(b);
    print(c);
}