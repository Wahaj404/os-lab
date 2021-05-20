#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int const maxConcurrent = 1;
sem_t _sem, *const sem = &_sem;

int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

typedef struct {
    int start;
    int end;
} Arg;

int sum = 0;

void *add(void *argg) {
    Arg *arg = (Arg *) argg;
    if (arg->end - arg->start == 1) {
        sem_wait(sem);
        alarm(2);
        sum += arr[arg->start];
        pause();
    } else {
        Arg left = *arg, right = *arg;
        left.end = (left.start + left.end) / 2;
        right.start = (right.start + right.end) / 2;
        pthread_t lid = 0, rid = 0;
        pthread_create(&lid, NULL, add, &left);
        pthread_create(&rid, NULL, add, &right);
        pthread_join(lid, NULL);
        pthread_join(rid, NULL);
    }
    return NULL;
}

void alarmHandler(int signo) {
    // reset handler
    if (signal(SIGALRM, alarmHandler) == SIG_ERR)
        puts("Can't catch SIGALRM");
    sem_post(sem);
    pthread_exit(NULL);
}

int main() {
    sem_init(sem, 0, maxConcurrent);
    if (signal(SIGALRM, alarmHandler) == SIG_ERR)
        puts("Can't catch SIGALRM");
    Arg begin = {0, 10};
    pthread_t id = 0;
    pthread_create(&id, NULL, add, &begin);
    pthread_join(id, NULL);
    printf("%d\n", sum);
    sem_destroy(sem);
}