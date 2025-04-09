#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define num_read 3
#define num_write 2
#define num_iter 2

int sh_data = 0, read_cnt = 0;
sem_t mutex, wr_lock, re_lock;

void *reader(void *arg)
{
    int read_id = *((int *)arg);
    for (int i = 0; i < num_iter; i++)
    {
        sem_wait(&re_lock);
        sem_wait(&mutex);
        read_cnt++;
        if (read_cnt == 1)
        {
            sem_wait(&wr_lock);
        }
        sem_post(&mutex);
        sem_post(&re_lock);

        printf("Reader %d is reading value %d\n", read_id, sh_data);
        sleep(2);
        sem_wait(&mutex);

        read_cnt--;
        if (read_cnt == 0)
        {
            sem_post(&wr_lock);
        }
        sem_post(&mutex);
        ;
        sleep(1);
    }
    return NULL;
}

void *writer(void *arg)
{
    int write_id = *((int *)arg);
    for (int i = 0; i < num_iter; i++)
    {
        sem_wait(&wr_lock);
        sh_data++;
        printf("Writer %d is writing values %d\n", write_id, sh_data);
        sleep(2);
        sem_post(&wr_lock);
        sleep(3);
    }
    return NULL;
}

int main()
{
    pthread_t readers[num_read], writers[num_write];
    int read_id[num_read], write_id[num_write];

    sem_init(&mutex, 0, 1);
    sem_init(&re_lock, 0, 1);
    sem_init(&wr_lock, 0, 1);

    for (int i = 0; i < num_write; i++)
    {
        write_id[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &write_id[i]);
    }
    for (int i = 0; i < num_read; i++)
    {
        read_id[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &read_id[i]);
    }

    for (int i = 0; i < num_write; i++)
    {
        pthread_join(writers[i], NULL);
    }
    for (int i = 0; i < num_read; i++)
    {
        pthread_join(readers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&re_lock);
    sem_destroy(&wr_lock);
}
