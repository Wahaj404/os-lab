#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define participants 1000

void *registration(void *arg) {
    for (int i = 0; i < participants; ++i) {
        sleep(1);
        printf("On day registration %d\n", i + 1);
    }
}

void *announcements(void *arg) {
    for (int i = 0; i < participants; ++i) {
        sleep(2);
        printf("Announcement %d\n", i + 1);
    }
}

void *sponsors(void *arg) {
    for (int i = 0; i < participants; ++i) {
        sleep(3);
        printf("Sponsor %d\n", i + 1);
    }
}

void *queries(void *arg) {
    for (int i = 0; i < participants; ++i) {
        sleep(4);
        printf("Query %d\n", i + 1);
    }
}

int main() {
    pthread_t a, b, c, d;
    pthread_create(&a, NULL, registration, NULL);
    pthread_create(&b, NULL, announcements, NULL);
    pthread_create(&c, NULL, sponsors, NULL);
    pthread_create(&d, NULL, queries, NULL);
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    pthread_join(c, NULL);
    pthread_join(d, NULL);
}