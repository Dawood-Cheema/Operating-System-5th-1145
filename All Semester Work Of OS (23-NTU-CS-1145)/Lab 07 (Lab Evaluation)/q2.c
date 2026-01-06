/*  Write a C program that calculates array sum using multiple threads:

1.  Create an array of 20 integers: {1, 2, 3, ..., 20}
2.  Create 4 threads, each calculating sum of 5 elements:   

Thread 1: elements 0-4 (sum of 1 to 5)
Thread 2: elements 5-9 (sum of 6 to 10)
Thread 3: elements 10-14 (sum of 11 to 15)
Thread 4: elements 15-19 (sum of 16 to 20)

3.  Pass the starting index and count to each thread using a structure:
4.  Each thread prints its partial sum
5.  Main thread collects all return values and calculates total sum


*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 20
#define THREAD_COUNT 4
#define CHUNK_SIZE (ARRAY_SIZE / THREAD_COUNT)

int arr[ARRAY_SIZE]; // array with values 1..20

// Structure to pass to each thread
typedef struct {
    int thread_id;   // 1..4 for identification
    int start_idx;   // starting index in arr
    int count;       // number of elements to sum (5)
} thread_arg_t;

// Thread routine: computes partial sum and returns pointer to int containing the sum
void* partial_sum(void* arg) {
    thread_arg_t* t = (thread_arg_t*)arg;
    int start = t->start_idx;
    int count = t->count;
    int sum = 0;

    for (int i = 0; i < count; ++i) {
        sum += arr[start + i];
    }

    // Print partial sum
    printf("Thread %d: elements %d to %d -> partial sum = %d\n",
           t->thread_id, start, start + count - 1, sum);

    // Allocate memory to return the result (caller must free)
    int* ret = (int*) malloc(sizeof(int));
    if (ret == NULL) {
        perror("malloc");
        pthread_exit(NULL);
    }
    *ret = sum;
    pthread_exit((void*)ret);
}

int main(void) {
    // initialize array with values 1..20
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arr[i] = i + 1;
    }

    pthread_t threads[THREAD_COUNT];
    thread_arg_t args[THREAD_COUNT];

    // create threads
    for (int i = 0; i < THREAD_COUNT; ++i) {
        args[i].thread_id = i + 1;
        args[i].start_idx = i * CHUNK_SIZE;
        args[i].count = CHUNK_SIZE;

        if (pthread_create(&threads[i], NULL, partial_sum, &args[i]) != 0) {
            perror("pthread_create");
            // If thread creation fails, clean up previously created threads
            for (int j = 0; j < i; ++j) {
                pthread_join(threads[j], NULL);
            }
            return EXIT_FAILURE;
        }
    }

    // collect results
    int total_sum = 0;
    for (int i = 0; i < THREAD_COUNT; ++i) {
        int* partial_result = NULL;
        if (pthread_join(threads[i], (void**)&partial_result) != 0) {
            perror("pthread_join");
            return EXIT_FAILURE;
        }
        if (partial_result != NULL) {
            total_sum += *partial_result;
            free(partial_result);
        }
    }

    printf("\nTotal sum = %d\n", total_sum);

    return 0;
}
