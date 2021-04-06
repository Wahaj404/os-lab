#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void print(int start) {
    for (int i = start; i <= 10; i += 2) {
        printf("%d ", i);
    }
    puts("");
}

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        puts("Unsuccessful child process creation");
        exit(1);
    } else if (pid > 0) {
        wait(NULL);
        print(2);
        puts("Parent ends");
    } else {
        printf("Parent PID: %d\n", getppid());
        print(1);
        puts("Child ends");
    }
    return 0;
}