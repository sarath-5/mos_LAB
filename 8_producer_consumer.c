#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
47
int in = 0;
int out = 0;
sem_t emptySlots;
sem_t filledSlots;
pthread_mutex_t bufferMutex;
void* producer(void* arg) {
int item = 1;
while (1) {
// Wait for an empty slot in the buffer
sem_wait(&emptySlots);
// Acquire the buffer mutex
pthread_mutex_lock(&bufferMutex);
// Produce an item and add it to the buffer
buffer[in] = item;
printf("Produced item: %d
\n", item);
in = (in + 1) % BUFFER_SIZE;
// Release the buffer mutex
pthread_mutex_unlock(&bufferMutex);
// Signal that a slot has been filled
sem_post(&filledSlots);
item++;
sleep(1);
}
return NULL;
}
void* consumer(void* arg) {
while (1) {
// Wait for a filled slot in the buffer
sem_wait(&filledSlots);
// Acquire the buffer mutex
pthread_mutex_lock(&bufferMutex);
// Consume an item from the buffer
int item = buffer[out];
printf("Consumed item: %d
\n", item);
out = (out + 1) % BUFFER_SIZE;
// Release the buffer mutex
pthread_mutex_unlock(&bufferMutex);
// Signal that an empty slot is available
sem_post(&emptySlots);
sleep(2);
}
return NULL;
}
48
int main() {
// Initialize semaphores and mutex
sem_init(&emptySlots, 0, BUFFER_SIZE);
sem_init(&filledSlots, 0, 0);
pthread_mutex_init(&bufferMutex, NULL);
// Create producer and consumer threads
pthread_t producerThread, consumerThread;
pthread_create(&producerThread, NULL, producer, NULL);
pthread_create(&consumerThread, NULL, consumer, NULL);
// Wait for threads to finish (which will never happen in this case)
pthread_join(producerThread, NULL);
pthread_join(consumerThread, NULL);
// Clean up semaphores and mutex
sem_destroy(&emptySlots);
sem_destroy(&filledSlots);
pthread_mutex_destroy(&bufferMutex);
return 0;
}