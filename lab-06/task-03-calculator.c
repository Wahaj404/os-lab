#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    key_t const key = 3142;
    int shmid = shmget(key, 100, IPC_CREAT | 0666);
    char *shm = shmat(shmid, NULL, 0);

    int n = 0, i = 1;
    sscanf(shm, "%d", &n);

    sprintf(shm, "ready");

    while (i <= 10) {
        while (*shm != '*') {
            sleep(1);
        }
        sprintf(shm, "%d", n * i++);
    }
    while (*shm != '*') {
        sleep(1);
    }
    *shm = 0;

    return 0;
}