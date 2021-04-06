#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main() {
    key_t const key = 3141;
    int shmid = shmget(key, 100, IPC_CREAT | 0666);
    char *shm = shmat(shmid, NULL, 0);
    *shm = '1';
    *(shm + 1) = 0;
    return 0;
}