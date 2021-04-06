#include <pthread.h>
#include <stdio.h>

#define len(arr) sizeof(arr) / sizeof(arr[0])

void *start(void *i) {
    static int zero = 0;
    printf("Thread %d\n", *((int *) i) + 1);
    return &zero;
}

int main() {
    pthread_t ids[3];
    void *ret[len(ids)] = {NULL};
    for (int i = 0; i < len(ids); ++i) {
        if (pthread_create(ids + i, NULL, start, &i) != 0) {
            puts("Error");
        } else {
            pthread_join(ids[i], ret + i);
        }
    }
    for (int i = 0; i < len(ids); ++i) {
        printf("Thread %d returned %d\n", i + 1, *((int *) ret[i]));
    }
}