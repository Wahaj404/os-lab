#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define length(array) sizeof(array) / sizeof(array[0])

pid_t origin;

typedef struct Node {
    char name[12];
    struct Node *children;
    int count;
} Node;

void ctor(Node *node, char const *name) {
    strcpy(node->name, name);
    node->children = NULL;
    node->count = 0;
}

void dtor(Node *node) {
    for (int i = 0; i < node->count; ++i) {
        dtor(node->children + i);
    }
    free(node->children);
}

void populate(Node *node, const char *names[], int count) {
    node->children = calloc(count, sizeof(Node));
    for (int i = 0; i < count; ++i) {
        ctor(node->children + i, names[i]);
    }
    node->count = count;
}

void print(Node const *node, int level) {
    for (int i = 0; i < level; ++i) {
        putchar('\t');
    }
    printf("I am process %s and my id is %d\n", node->name, getpid());
}

void nextLevel(Node const *node, int level) {
    print(node, level);
    for (int i = 0; i < node->count; ++i) {
        if (fork() == 0) {
            nextLevel(node->children + i, level + 1);
            break;
        }
        wait(NULL);
    }
    if (origin != getpid()) {
        exit(0);
    }
}

Node tree1();
Node tree2();
Node tree3();
Node tree4();
Node tree5();
Node tree6();
Node tree7();
Node tree8();
Node tree9();

int main() {
    origin = getpid();
    Node (*trees[])() = {tree1, tree2, tree3, tree4, tree5,
                         tree6, tree7, tree8, tree9};
    for (int i = 0; i < length(trees); ++i) {
        Node head = trees[i]();
        nextLevel(&head, 0);
        wait(NULL);
        if (origin == getpid()) {
            dtor(&head);
        }
        puts("");
    }
    return 0;
}

Node tree1() {
    char const *a[] = {"5", "3"};
    char const *b[] = {"4"};
    Node head = {"1", NULL, 0};
    populate(&head, a, length(a));
    populate(head.children + 1, b, length(b));
    return head;
}

Node tree2() {
    char const *a[] = {"9"};
    Node head = {"6", NULL, 0};
    populate(&head, a, length(a));
    return head;
}

Node tree3() {
    char const *a[] = {"0"};
    char const *b[] = {"7", "2"};
    Node head = {"8", NULL, 0};
    populate(&head, a, length(a));
    populate(head.children, b, length(b));
    return head;
}

Node tree4() {
    char const *a[] = {"inner node", "leaf"};
    char const *b[] = {"leaf", "leaf"};
    Node head = {"root", NULL, 0};
    populate(&head, a, length(a));
    populate(head.children, b, length(b));
    return head;
}

Node tree5() {
    char const *a[] = {"B", "C", "D"};
    char const *b[] = {"E", "F"};
    char const *c[] = {"G", "H"};
    Node head = {"A", NULL, 0};
    populate(&head, a, length(a));
    populate(head.children, b, length(b));
    populate(head.children + 2, c, length(c));
    return head;
}

Node tree6() {
    char const *a[] = {"B", "C", "D"};
    char const *b[] = {"E"};
    char const *c[] = {"F", "G"};
    Node head = {"A", NULL, 0};
    populate(&head, a, length(a));
    populate(head.children, b, length(b));
    populate(head.children + 1, c, length(c));
    return head;
}

Node tree7() {
    char const *a[] = {"6", "18"};
    char const *b[] = {"4", "8"};
    char const *c[] = {"15", "21"};
    Node head = {"10", NULL, 0};
    populate(&head, a, length(a));
    populate(head.children, b, length(b));
    populate(head.children + 1, c, length(c));
    return head;
}

Node tree8() {
    char const *a[] = {"B", "C"};
    char const *b[] = {"D"};
    char const *c[] = {"E", "F"};
    Node head = {"A", NULL, 0};
    populate(&head, a, length(a));
    populate(head.children, b, length(b));
    populate(head.children + 1, c, length(c));
    return head;
}

Node tree9() {
    char const *a[] = {"2", "3"};
    char const *b[] = {"4", "5"};
    char const *c[] = {"6", "7"};
    char const *d[] = {"8", "9"};
    Node head = {"1", NULL, 0};
    populate(&head, a, length(a));
    populate(head.children, b, length(b));
    populate(head.children + 1, c, length(c));
    populate(head.children->children, d, length(d));
    return head;
}
