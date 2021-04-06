#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    if (fork() == 0) {
        if (fork() == 0) {
            if (fork() == 0) {
                execlp("ls", "ls", "-aR1", NULL);
            } else {
                wait(NULL);
            }
        } else {
            wait(NULL);
        }
    } else {
        wait(NULL);
    }
    return 0;
}