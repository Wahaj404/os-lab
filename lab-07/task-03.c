#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *identify(void *arg) {
    static int zero = 0;
    int *p = (int *) arg;
    printf("Hello from thread %d - I was created in iteration %d\n", *p, *p);
    return &zero;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        puts("number of threads must be provided");
        exit(1);
    }
    int i = 0, n = 0;
    sscanf(argv[1], "%d", &n);
    while (i < n) {
        for (int j = 0; i < n && j < 5; ++j) {
            pthread_t id = 0;
            pthread_create(&id, NULL, identify, &i);
            printf("I am thread 1. Created new thread (%d) in iteration %d\n",
                   i, i);
            ++i;
        }
        sleep(1);
    }
}