#include <pthread.h>
#include <stdio.h>

void *table(void *n) {
    static int zero = 0;
    for (int i = 0; i < 10; ++i) {
        printf("\t%d", (*((int *) n) + 5) * (i + 1));
    }
    puts("");
    return &zero;
}

int main() {
    for (int i = 0; i < 4; ++i) {
        pthread_t id;
        if (pthread_create(&id, NULL, table, &i) != 0) {
            puts("Error");
        } else {
            pthread_join(id, NULL);
        }
    }
}