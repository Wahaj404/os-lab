#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int counter = 0;
    pid_t pid = fork();
    for (counter = 0; counter < 5; ++counter) {
        printf("Counter: %d\n", counter + 1);
    }
    if (pid == 0) {
        sleep(3);
        execl("/usr/bin/gedit", "", NULL);
    } else {
        wait(NULL);
    }
    return 0;
}