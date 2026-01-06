#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t resource_semaphore;
void* thread_function(void* arg) {

int thread_id = *(int*)arg;
printf("Thread %d: Waiting for resource...\n", thread_id);

//sem_wait(&resource_semaphore); // Wait: decrement counter
printf("Thread %d: Acquired resource!\n", thread_id);
sleep(2); // Use resource

printf("Thread %d: Releasing resource...\n", thread_id);
sem_post(&resource_semaphore); // Signal: increment counter
return NULL;
}


int main() {
sem_init(&resource_semaphore, 0, 3); // Allow 3 concurrent threads
pthread_t threads[5];
int ids[5];
for (int i = 0; i < 5; i++) {
ids[i] = i;
pthread_create(&threads[i], NULL, thread_function, &ids[i]);
}

for (int i = 0; i < 5; i++) {
pthread_join(threads[i], NULL);
}
sem_destroy(&resource_semaphore);
return 0;
}