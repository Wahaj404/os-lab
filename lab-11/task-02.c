#include <pthread.h>
#include <semaphore.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int const customers = 10;
int const maxConcurrent = 1;
sem_t weighingSem, *const weighingSemaphore = &weighingSem;
sem_t checkingSem, *const checkingSemaphore = &checkingSem;
sem_t boardingSem, *const boardingSemaphore = &boardingSem;
time_t start = 0;

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

void weigh(long c) {
    sem_wait(weighingSemaphore);
    timedPrint("Person %ld starting to weigh luggage\n", c);
    sleep(4);
    timedPrint("Person %ld done weighing luggage\n", c);
    sem_post(weighingSemaphore);
}

void check(long c) {
    sem_wait(checkingSemaphore);
    timedPrint("Person %ld starting to check luggage\n", c);
    sleep(7);
    timedPrint("Person %ld done checking luggage\n", c);
    sem_post(checkingSemaphore);
}

void board(long c) {
    sem_wait(boardingSemaphore);
    timedPrint("Person %ld starting to get boarding pass\n", c);
    sleep(3);
    timedPrint("Person %ld done getting boarding pass\n", c);
    sem_post(boardingSemaphore);
}

void *customerProcess(void *cnt) {
    long c = (long) cnt;
    weigh(c);
    check(c);
    board(c);
    return NULL;
}

int main() {
    start = time(NULL);
    sem_init(weighingSemaphore, 0, maxConcurrent);
    sem_init(checkingSemaphore, 0, maxConcurrent);
    sem_init(boardingSemaphore, 0, maxConcurrent);
    pthread_t tids[customers];
    for (long i = 0; i < customers; ++i) {
        pthread_create(tids + i, NULL, customerProcess, (void *) i + 1);
    }
    for (int i = 0; i < customers; ++i) {
        pthread_join(tids[i], NULL);
    }
    sem_destroy(boardingSemaphore);
    sem_destroy(checkingSemaphore);
    sem_destroy(weighingSemaphore);
}