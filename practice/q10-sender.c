#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define len(arr) sizeof(arr) / sizeof(arr[0])

int main() {
    char *fruits[] = {"apple",      "mango",    "pomogrenate", "guava",
                      "banana",     "orange",   "melon",       "grape",
                      "strawberry", "pineapple"};
    char *args[7] = {"./q10-receiver.sh", NULL};
    char *env[] = {NULL};
    for (int i = 1; i < len(args) - 1; ++i) {
        args[i] = fruits[rand() % len(fruits)];
    }
    execve(args[0], args, env);
    return 0;
}