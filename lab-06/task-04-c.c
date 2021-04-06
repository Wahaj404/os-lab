#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void putm(char *shm, int n) {
    sprintf(shm, "%d", n);
}

int getm(char const *shm) {
    int n = 0;
    sscanf(shm, "%d", &n);
    return n;
}

int main(int argc, char *argv[]) {
    int cnt = 0;
    if (argc >= 2) {
        sscanf(argv[1], "%d", &cnt);
    } else {
        printf("Enter number of terms: ");
        scanf("%d", &cnt);
    }
    key_t const akey = 3140, bkey = 3141;
    int ashmid = shmget(akey, 100, IPC_CREAT | 0666),
        bshmid = shmget(bkey, 100, IPC_CREAT | 0666);
    char *ashm = shmat(ashmid, NULL, 0), *bshm = shmat(bshmid, NULL, 0);
    while (cnt--) {
        int a = getm(ashm), b = getm(bshm);
        putm(ashm, b), putm(bshm, a + b);
        printf("%d ", a);
    }
    puts("");
    return 0;
}