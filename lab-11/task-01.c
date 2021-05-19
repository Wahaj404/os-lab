#include <pthread.h>
#include <semaphore.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int const customers = 3;
int const maxConcurrent = 1;
sem_t sem, *const semaphore = &sem;
time_t start = 0;

int randRange(int start, int end) {
    return rand() % (end - start + 1) + start;
}

long curTime() {
    return time(NULL) - start;
}

void timedPrint(char const *fmt, ...) {
    printf("[%2ld] ", curTime(NULL));
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

void *eat(void *cnt) {
    sem_wait(semaphore);
    timedPrint("Person %ld starting to eat ice cream\n", (long) cnt);
    sleep(randRange(1, 5));
    timedPrint("Person %ld done eating ice cream\n", (long) cnt);
    sem_post(semaphore);
    timedPrint("Person %ld starting to count change\n", (long) cnt);
    sleep(randRange(1, 2));
    timedPrint("Person %ld done counting change\n", (long) cnt);
    return NULL;
}

int main() {
    start = time(NULL);
    sem_init(semaphore, 0, maxConcurrent);
    pthread_t tids[customers];
    for (long i = 0; i < customers; ++i) {
        pthread_create(tids + i, NULL, eat, (void *) i + 1);
    }
    for (int i = 0; i < customers; ++i) {
        pthread_join(tids[i], NULL);
    }
    sem_destroy(semaphore);
}