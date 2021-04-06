#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    for (int i = 0; i < 3; ++i) {
        char fname[30], buffer[16];
        sprintf(fname, "/tmp/task02fifo%d", i + 1);
        sprintf(buffer, "Testdata for %d", i + 1);
        int retval = mkfifo(fname, 0666), fd = open(fname, O_WRONLY);
        write(fd, buffer, sizeof(buffer));
        close(fd);
    }
    return 0;
}