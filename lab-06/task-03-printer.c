#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main() {
    srand(time(NULL));
    key_t const key = 3142;
    int shmid = shmget(key, 100, IPC_CREAT | 0666);
    char *shm = shmat(shmid, NULL, 0);
    sprintf(shm, "%d", rand() % 10 + 1);

    while (strcmp(shm, "ready") != 0) {
        sleep(1);
    }
    puts(shm);

    while (1) {
        *shm = '*';
        while (*shm == '*') {
            sleep(1);
        }
        if (puts(shm) == 1) {
            break;
        }
    }
}