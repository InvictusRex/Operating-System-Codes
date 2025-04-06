#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

typedef enum { THINKING, HUNGRY, EATING } State;
State state[NUM_PHILOSOPHERS];

pthread_mutex_t mutex; // Monitor mutex
pthread_cond_t cond[NUM_PHILOSOPHERS]; // Condition variables

void test(int id) {
    if (state[id] == HUNGRY &&
        state[(id + 4) % NUM_PHILOSOPHERS] != EATING &&
        state[(id + 1) % NUM_PHILOSOPHERS] != EATING) {
        state[id] = EATING;
        pthread_cond_signal(&cond[id]);
    }
}

void pickup_chopsticks(int id) {
    pthread_mutex_lock(&mutex);
    state[id] = HUNGRY;
    printf("Philosopher %d is hungry and trying to eat...\n", id);
    test(id); // Try to acquire chopsticks
    if (state[id] != EATING) {
        pthread_cond_wait(&cond[id], &mutex); // Wait if unable to eat
    }
    pthread_mutex_unlock(&mutex);
}

void putdown_chopsticks(int id) {
    pthread_mutex_lock(&mutex);
    state[id] = THINKING;
    printf("Philosopher %d finished eating and is now thinking...\n", id);
    test((id + 4) % NUM_PHILOSOPHERS);
    test((id + 1) % NUM_PHILOSOPHERS);
    pthread_mutex_unlock(&mutex);
}

void* philosopher(void* num) {
    int id = *(int*)num;
    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(rand() % 3 + 1);
        pickup_chopsticks(id);
        printf("Philosopher %d is eating...\n", id);
        sleep(rand() % 2 + 1);
        putdown_chopsticks(id);
    }
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_cond_init(&cond[i], NULL);
        state[i] = THINKING;
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(philosophers[i], NULL);

    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_cond_destroy(&cond[i]);

    return 0;
}
