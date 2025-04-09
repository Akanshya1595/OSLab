#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define buf_size 5
#define num_pr 2
#define num_co 2
#define num_it 5

int buffer[buf_size];
int in = 0, out = 0;
sem_t empty, full, mutex;

void *producers(void *arg)
{
    int pr_id = *((int *)arg);
    int it;
    for (int i = 0; i < num_it; i++)
    {
        it = rand() % 104;
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = it;
        printf("Producer %d produced item %d at %d\n", pr_id, buffer[in], in);
        in = (in + 1) % buf_size;
        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    }
    return NULL;
}

void *consumers(void *arg)
{
    int cons_id = *((int *)arg);
    int it;
    for (int i = 0; i < num_it; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        it = buffer[out];
        printf("Consumer %d consumer item %d at %d\n", cons_id, buffer[out], out);
        out = (out + 1) % buf_size;
        sem_post(&mutex);
        sem_post(&empty);
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t producer[num_pr], consumer[num_co];
    int prod_id[num_pr], cons_id[num_co];

    sem_init(&empty, 0, buf_size);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < num_pr; i++)
    {
        prod_id[i] = i;
        pthread_create(&producer[i], NULL, producers, &prod_id[i]);
    }

    for (int i = 0; i < num_co; i++)
    {
        cons_id[i] = i;
        pthread_create(&consumer[i], NULL, consumers, &cons_id[i]);
    }

    for (int i = 0; i < num_pr; i++)
    {
        pthread_join(producer[i], NULL);
    }
    for (int i = 0; i < num_co; i++)
    {
        pthread_join(consumer[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
