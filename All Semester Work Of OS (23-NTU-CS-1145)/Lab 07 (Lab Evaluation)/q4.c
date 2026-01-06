/*    Write a C Program and Create a shared global variable

2.  Create 4 threads:
Thread 1: Deposits 1000 (repeat 5 times)
Thread 2: Withdraws 500 (repeat 5 times)
Thread 3: Deposits 800 (repeat 5 times)
Thread 4: Withdraws 300 (repeat 5 times)

3.  Use mutex to protect balance updates
4.  Each thread should print after each transaction: Thread ID

Operation (Deposit/Withdraw)  
Amount initialized to 5000
New balance
Main thread print final balence
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>   // for usleep (optional, to better show interleaving)

/* Shared global balance */
long balance = 5000;

/* Mutex to protect balance updates */
pthread_mutex_t balance_mutex = PTHREAD_MUTEX_INITIALIZER;

/* Structure to pass parameters to threads */
typedef struct {
    int thread_id;        // 1..4
    const char *op;       // "Deposit" or "Withdraw"
    long amount;          // amount per operation
    int repeats;          // how many times to perform
} txn_arg_t;

/* Thread routine */
void* transaction_thread(void* arg) {
    txn_arg_t *t = (txn_arg_t*)arg;

    for (int i = 0; i < t->repeats; ++i) {
        /* Acquire mutex before accessing/modifying balance */
        pthread_mutex_lock(&balance_mutex);

        if (t->op[0] == 'D') { /* Deposit */
            balance += t->amount;
            printf("Thread %d | %s | Amount: %ld | New balance: %ld\n",
                   t->thread_id, t->op, t->amount, balance);
        } else { /* Withdraw */
            if (balance >= t->amount) {
                balance -= t->amount;
                printf("Thread %d | %s | Amount: %ld | New balance: %ld\n",
                       t->thread_id, t->op, t->amount, balance);
            } else {
                /* If insufficient funds, skip withdrawal (safe behavior) */
                printf("Thread %d | %s | Amount: %ld | FAILED - Insufficient funds (balance: %ld)\n",
                       t->thread_id, t->op, t->amount, balance);
            }
        }

        /* Release mutex so other threads can operate */
        pthread_mutex_unlock(&balance_mutex);

        /* Small sleep to allow other threads to run and to show interleaving (optional) */
        usleep(100000); // 100 ms
    }

    return NULL;
}

int main(void) {
    pthread_t threads[4];
    txn_arg_t args[4];

    /* Initialize thread arguments per specification */
    args[0].thread_id = 1; args[0].op = "Deposit";  args[0].amount = 1000; args[0].repeats = 5;
    args[1].thread_id = 2; args[1].op = "Withdraw"; args[1].amount = 500;  args[1].repeats = 5;
    args[2].thread_id = 3; args[2].op = "Deposit";  args[2].amount = 800;  args[2].repeats = 5;
    args[3].thread_id = 4; args[3].op = "Withdraw"; args[3].amount = 300;  args[3].repeats = 5;

    printf("Initial balance: %ld\n\n", balance);

    /* Create threads */
    for (int i = 0; i < 4; ++i) {
        if (pthread_create(&threads[i], NULL, transaction_thread, &args[i]) != 0) {
            perror("pthread_create");
            return EXIT_FAILURE;
        }
    }

    /* Wait for all threads to finish */
    for (int i = 0; i < 4; ++i) {
        pthread_join(threads[i], NULL);
    }

    /* Final balance printed by main thread */
    printf("\nFinal balance: %ld\n", balance);

    /* Cleanup mutex (not strictly necessary at program end, but good practice) */
    pthread_mutex_destroy(&balance_mutex);

    return 0;
}
