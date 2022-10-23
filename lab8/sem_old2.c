#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int count = 0; 
// sem_t mutex; // need to shared with 2 thread, so global var
sem_t *mutex, *full, *empty;
int buffer[5];

void *insertBuffer(void *param);
void *readBuffer(void *param);
int main() {
	pthread_t tid1, tid2;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

    mutex = sem_open("/semaphore", O_CREAT, 0666, 1); // 1 is value
    full = sem_open("/semaphore", O_CREAT, 0666, 0);
    empty = sem_open("/semaphore", O_CREAT, 0666, BUFFER_SIZE);

	pthread_create(&tid1, &attr, insertBuffer, NULL);
	pthread_create(&tid2, &attr, readBuffer, NULL);
	/* now wait for the thread to exit */
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	// printf("count  = %d\n", count); // old

	// sem_close(&mutex); // shared memory, ใช้เสร็จ remove ออก
    sem_close(mutex);
    sem_close(full);
    sem_close(empty);
	sem_unlink("/semaphore");
}

void *insertBuffer(void *param) {
    int in = 0;
	for(int i = 0; i < 40; i++){
        sem_wait(empty);
        sem_wait(mutex);

        while(count == BUFFER_SIZE);
        buffer[in] = i;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        printf("Producer Entered %d Buffer size = %d\n", buffer[in], in);

        sem_post(mutex);
        sem_post(full);
        // pthread_exit(0);

        // may be can print after sending signal ***
    }
}

void *readBuffer(void *param) {
    int out = 5;
	for(int i = 0; i < 40; i++){
        sem_wait(full);
        sem_wait(mutex);

        while(count == 0);
        out = (out - 1) % BUFFER_SIZE; // read from right to left
        count--;

        printf("Consumer consumed %d buffer size = %d\n", buffer[out], out);

        sem_post(mutex);
        sem_post(empty);
        // pthread_exit(0);
    }
}
