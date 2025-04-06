#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;
int read_count = 0;

void *reader(void *arg) {
    int id = *(int *)arg;

    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&wrt);  // First reader locks the writer
    sem_post(&mutex);

    printf("Reader %d is reading\n", id);
    sleep(1);

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&wrt);  // Last reader unlocks the writer
    sem_post(&mutex);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

    sem_wait(&wrt);  // Writer locks
    printf("Writer %d is writing\n", id);
    sleep(2);
    sem_post(&wrt);  // Writer unlocks

    return NULL;
}

int main() {
    pthread_t readers[5], writers[2];
    int ids[5] = {1, 2, 3, 4, 5};

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader threads
    for (int i = 0; i < 5; i++)
        pthread_create(&readers[i], NULL, reader, &ids[i]);

    // Create writer threads
    for (int i = 0; i < 2; i++)
        pthread_create(&writers[i], NULL, writer, &ids[i]);

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++)
        pthread_join(readers[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(writers[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
