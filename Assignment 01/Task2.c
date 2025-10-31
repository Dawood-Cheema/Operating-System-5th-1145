// Task 2 – Personalized Greeting Thread
// Dawood Saif
// Reg. No. 23-NTU-CS-1145

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *greet(void *arg) {
    char *name = (char*)arg;
    printf("Thread says: Hello, %s! Welcome to the world of threads.\n", name);
    free(name);
    return NULL;
}

int main() {
    pthread_t tid;
    char *name = strdup("Dawood Saif");

    printf("Main thread: Waiting for greeting...\n");
    pthread_create(&tid, NULL, greet, name);
    pthread_join(tid, NULL);
    printf("Main thread: Greeting completed.\n");
    return 0;
}