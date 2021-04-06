#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

typedef struct {
    int start;
    int end;
} Arg;

int m = 0;

void *sum(void *argg) {
    Arg *arg = (Arg *) argg;
    int *ret = malloc(sizeof(int));
    if (arg->end - arg->start == 1) {
        *ret = arr[arg->start];
    } else {
        Arg left = *arg, right = *arg;
        left.end = (left.start + left.end) / 2;
        right.start = (right.start + right.end) / 2;
        pthread_t rid = 0;
        pthread_create(&rid, NULL, sum, &right);
        int *lret = sum(&left), *rret = NULL;
        pthread_join(rid, (void *) &rret);
        *ret = *lret + *rret;
        free(lret);
        free(rret);
    }
    return ret;
}

int main() {
    Arg begin = {0, 10};
    int *s = sum(&begin);
    printf("%d\n", *s);
    free(s);
}