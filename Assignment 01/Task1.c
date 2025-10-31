// Task 1 – Thread Information Display
// Dawood Saif
// Reg. No. 23-NTU-CS-1145

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_func(void *arg) {
    int *num = (int*)arg;
    int id = *num;
    pthread_t tid = pthread_self();
    printf("Thread %d: pthread_self() = %lu\n", id, (unsigned long)tid);

    int sleep_time = (rand() % 3) + 1; // 1-3 seconds
    printf("Thread %d: sleeping %d sec\n", id, sleep_time);
    sleep(sleep_time);

    printf("Thread %d: completed\n", id);
    free(arg);
    return NULL;
}

int main() {
    pthread_t threads[5];
    for (int i = 0; i < 5; i++) {
        int *arg = malloc(sizeof(int));
        *arg = i + 1;
        pthread_create(&threads[i], NULL, thread_func, arg);
        
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Hello This is the main thread!\n");
    return 0;
}