//  Task 3 – Number Information Display
//  Dawood Saif
//  Reg. No. 23-NTU-CS-1145

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *number_info(void *arg) {
    int n = *(int*)arg;
    printf("Thread: Number = %d\n", n);
    printf("Thread: Square = %d\n", n*n);
    printf("Thread: Cube = %d\n", n*n*n);
    free(arg);
    return NULL;
}

int main() {
    pthread_t tid;
    int *n = malloc(sizeof(int));
    printf("Enter an integer: ");
    scanf("%d", n);

    pthread_create(&tid, NULL, number_info, n);
    pthread_join(tid,NULL);
    printf("Main thread: Work completed.\n");
    return 0;
}