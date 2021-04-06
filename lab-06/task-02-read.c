#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd, retval;
    char buffer[16];
    char fname[30];
    sprintf(fname, "/tmp/task02fifo%s", argv[1]);
    fd = open(fname, O_RDONLY);
    retval = read(fd, buffer, sizeof(buffer));
    fflush(stdin);
    write(1, buffer, sizeof(buffer));
    printf("\n");
    close(fd);
    return 0;
}