#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t gpid = getppid();
    if (fork() == 0) {
        sleep(1);
        exit(16);
    } else if (fork() == 0) {
        // if (fork() == 0) {
        //     execlp("ifconfig", "ifconfig", "-a", NULL);
        // } else {
        //     wait(NULL);
        //     exit(1);
        // }
        system("ifconfig -a | grep -o 'ether [[:xdigit:]:]*'");
        exit(17);
    } else if (fork() == 0) {
        sleep(7);
        if (fork() == 0) {
            execlp("date", "date", NULL);
        } else {
            wait(NULL);
            exit(20);
        }
    } else if (fork() == 0) {
        printf("Grandparent pid: %d\n", gpid);
        exit(0);
    }

    for (int i = 0; i < 4; ++i) {
        int status = 0;
        pid_t pid = wait(&status);
        printf("%d exited with status %d\n", pid, WEXITSTATUS(status));
    }
    return 0;
}
