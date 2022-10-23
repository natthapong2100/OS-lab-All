#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int count = 0; 
// sem_t mutex; // need to shared with 2 thread, so global var
sem_t mutex, full, empty;
int buffer[5];

void *insertBuffer(void *param);
void *readBuffer(void *param);
int main() {
	pthread_t tid1, tid2;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

	pthread_create(&tid1, &attr, insertBuffer, NULL);
	pthread_create(&tid2, &attr, readBuffer, NULL);
	/* now wait for the thread to exit */
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	// printf("count  = %d\n", count); // old

    sem_destroy(&mutex);
    // sem_destroy(&full);
    // sem_destroy(&empty);
}

void *insertBuffer(void *param) {
    int in = 0;
	for(int i = 0; i < 40; i++){
        sem_wait(&empty);
        sem_wait(&mutex);

        while(count == BUFFER_SIZE)
            ;
        // buffer[in] = i;
        in = (in + 1) % BUFFER_SIZE;
        buffer[in] = i;

        count++;
        

        sem_post(&mutex);
        sem_post(&full);
        // pthread_exit(0);

        // may be can print after sending signal ***
        if(in == 0){
            printf("Producer Entered %d Buffer Full\n", buffer[in]);
        }
        else{
            printf("Producer Entered %d Buffer size = %d\n", buffer[in], count); // may be use count ***
        }
        
    }
}

void *readBuffer(void *param) {
    int out = 0;
	for(int i = 0; i < 40; i++){
        sem_wait(&full);
        sem_wait(&mutex);

        while(count == 0)
            ;
        out = (out + 1) % BUFFER_SIZE; // read from right to left
        count--;
        // printf("Consumer consumed %d buffer size = %d\n", buffer[out], count); // here
        // count--;

        sem_post(&mutex);
        sem_post(&empty);
        // pthread_exit(0);
        

        printf("Consumer consumed %d buffer size = %d\n", buffer[out], count);
    }
    // printf("Consumer consumed %d buffer size = %d\n", buffer[out], count); // here
}

// gcc -o sem sem.c
