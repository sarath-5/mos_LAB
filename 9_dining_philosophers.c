#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM_PHILOSOPHERS 5
// State constants for philosophers
#define THINKING 0
#define HUNGRY 1
#define EATING 2
// Mutex for critical sections
pthread_mutex_t mutex;
// Semaphores for philosophers
sem_t semaphores[NUM_PHILOSOPHERS];
// Array to track philosopher states
int philosopherState[NUM_PHILOSOPHERS];
// Array to track philosopher IDs
int philosopherIDs[NUM_PHILOSOPHERS];
void* philosopher(void* arg) {
int philosopherID = *(int*)arg;
int leftFork = philosopherID;
int rightFork = (philosopherID + 1) % NUM_PHILOSOPHERS;
while (1) {
// Think
printf("Philosopher %d is thinking.\n", philosopherID);
sleep(1);
// Get hungry
pthread_mutex_lock(&mutex);
51
philosopherState[philosopherID] = HUNGRY;
printf("Philosopher %d is hungry.\n", philosopherID);
pthread_mutex_unlock(&mutex);
// Try to acquire both forks
sem_wait(&semaphores[philosopherID]);
sem_wait(&semaphores[rightFork]);
// Eat
pthread_mutex_lock(&mutex);
philosopherState[philosopherID] = EATING;
printf("Philosopher %d is eating.\n", philosopherID);
pthread_mutex_unlock(&mutex);
sleep(2); // Simulate eating
// Release forks
sem_post(&semaphores[philosopherID]);
sem_post(&semaphores[rightFork]);
// Stop eating and go back to thinking
pthread_mutex_lock(&mutex);
philosopherState[philosopherID] = THINKING;
printf("Philosopher %d finished eating and is back to thinking.\n", philosopherID);
pthread_mutex_unlock(&mutex);
sleep(1);
}
return NULL;
}
int main() {
pthread_t philosophers[NUM_PHILOSOPHERS];
int i;
// Initialize mutex and semaphores
pthread_mutex_init(&mutex, NULL);
for (i = 0; i < NUM_PHILOSOPHERS; i++) {
sem_init(&semaphores[i], 0, 1);
philosopherIDs[i] = i;
}
// Create philosopher threads
for (i = 0; i < NUM_PHILOSOPHERS; i++) {
pthread_create(&philosophers[i], NULL, philosopher, &philosopherIDs[i]);
}
// Wait for philosopher threads to finish (which will never happen in this case)
for (i = 0; i < NUM_PHILOSOPHERS; i++) {
pthread_join(philosophers[i], NULL);
}
// Clean up mutex and semaphores
pthread_mutex_destroy(&mutex);
for (i = 0; i < NUM_PHILOSOPHERS; i++) {
52
sem_destroy(&semaphores[i]);
}
return 0;
}