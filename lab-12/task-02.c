#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#define setHandle(sig)                                                         \
    if (sigaction(sig, &sa, NULL) == SIG_ERR) {                                \
        puts("Can't catch " #sig);                                             \
    }

#define checkSignal(sig)                                                       \
    if (signo == sig) {                                                        \
        puts("Received " #sig);                                                \
    }

void sig_handler(int signo) {
    checkSignal(SIGUSR1);
    checkSignal(SIGKILL);
    checkSignal(SIGSTOP);
}

int main(void) {
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    setHandle(SIGUSR1);
    setHandle(SIGKILL);
    setHandle(SIGSTOP);
    while (1) {
        sleep(1);
    }
}