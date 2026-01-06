/*  Write a C program that creates 4 threads. Each thread should:

1.  Receive a unique number N as an argument (use values: 10, 20, 30, 40)
2.  Calculate the sum of numbers from 1 to N
3.  Print the thread number and calculated sum
4.  Return the sum through thread's return value

Main thread should:
Create all 4 threads and pass arguments Wait for all threads to complete

Collect all return values
Calculate and print the total of all sums     */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function executed by each thread
void* calculate_sum(void* arg) {
    int N = *(int*)arg;  // Get the integer value passed as argument
    int sum = 0;

    // Calculate the sum from 1 to N
    for (int i = 1; i <= N; i++) {
        sum += i;
    }

    printf("Thread for N = %d → Sum = %d\n", N, sum);

    // Dynamically allocate memory to return the result
    int* result = (int*)malloc(sizeof(int));
    *result = sum;
    pthread_exit((void*)result);  // Return sum to main thread
}

int main() {
    pthread_t threads[4];       // Array to hold 4 thread identifiers
    int values[4] = {10, 20, 30, 40}; // Each thread’s argument
    int* thread_result;         // To store returned sum
    int total_sum = 0;

    // Create 4 threads
    for (int i = 0; i < 4; i++) {
        if (pthread_create(&threads[i], NULL, calculate_sum, &values[i]) != 0) {
            printf("Error creating thread %d\n", i + 1);
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], (void**)&thread_result); // collect return value
        total_sum += *thread_result;
        free(thread_result);  // free allocated memory
    }

    // Print total sum collected from all threads
    printf("\nTotal of all sums = %d\n", total_sum);

    return 0;
}
