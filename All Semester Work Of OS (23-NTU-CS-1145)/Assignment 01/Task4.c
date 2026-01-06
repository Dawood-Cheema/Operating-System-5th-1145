//Task 4 – Thread Return Values
//Dawood Saif
//Reg. No. 23-NTU-CS-1145

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *factorial_thread(void *arg) {
    int n = *(int*)arg;
    free(arg);
    long int *result = malloc(sizeof(long int));
    *result = 1;
    for (int i = 1; i <= n; i++){
         *result *= i;
        };
    return (void*)result;
}

int main() {
    pthread_t tid;
    int *n = malloc(sizeof(int));
    printf("Enter number for factorial: ");
    scanf("%d", n);

    pthread_create(&tid, NULL, factorial_thread, n);
    void *res;
    pthread_join(tid, &res);
    long int *fact = (long int*)res;
    printf("Main thread: Factorial = %ld\n", *fact);
    free(fact);
    printf("Main thread: Done.\n");
    return 0;
}