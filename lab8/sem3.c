// namedsem

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int count = 0; 
// sem_t mutex; // need to shared with 2 thread, so global var
// sem_t *mutex, *full, *empty;
sem_t *full, *empty;
pthread_mutex_t mutex;

int buffer[5];

void *insertBuffer(void *param);
void *readBuffer(void *param);
int main() {
	pthread_t tid1, tid2;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

    // mutex = sem_open("/semaphore", O_CREAT, 0666, 1); // 1 is value
    pthread_mutex_init(&mutex, NULL);

    full = sem_open("/fully_sem", O_CREAT, 0666, 0);
    empty = sem_open("/empty_sem", O_CREAT, 0666, BUFFER_SIZE);

	pthread_create(&tid1, &attr, insertBuffer, NULL);
	pthread_create(&tid2, &attr, readBuffer, NULL);
	/* now wait for the thread to exit */
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	// printf("count  = %d\n", count); // old
  pthread_mutex_destroy(&mutex);
  sem_close(full);
  sem_close(empty);

	pthread_exit(0);

    // return 0;
}

void *insertBuffer(void *param) {
    int in = 0;
    int temp;
	for(int i = 0; i < 40; i++){
        sem_wait(empty);
        // sem_wait(mutex);
        pthread_mutex_lock(&mutex);

        // in = count;
        // while(in == BUFFER_SIZE)
        //     ;
        // in = (in + 1) % BUFFER_SIZE;
        // count = in;

        // prev section
        while(count == BUFFER_SIZE)
            ;
        
        in = (in + 1) % BUFFER_SIZE;
        buffer[in] = i;
        count++;

        // temp = count;
        // sleep(rand() % 5);
        // temp++;
        // count = temp;

        // printf("Producer Entered %d Buffer size = %d\n", buffer[in], in);

        // sem_post(mutex);
        pthread_mutex_unlock(&mutex);
        sem_post(full);
        // pthread_exit(0);

        if(in == 0){
            printf("Producer Entered %d Buffer Full\n", buffer[in]);
        }
        else{
            printf("Producer Entered %d Buffer size = %d\n", buffer[in], count); // may be use count ***
        }

        // may be can print after sending signal ***
    }
    pthread_exit(0);
}

void *readBuffer(void *param) {
    int out = 0;
	for(int i = 0; i < 40; i++){
        sem_wait(full);
        // sem_wait(mutex);
        pthread_mutex_lock(&mutex);

        // out = count;
        // while(out == BUFFER_SIZE);
        // out = (out - 1) % BUFFER_SIZE;
        // count = out;

        // prev section
        while(count == 0)
            ;
        out = (out + 1) % BUFFER_SIZE; // read from right to left
        
        count--;

        // sem_post(mutex);
        pthread_mutex_unlock(&mutex);
        sem_post(empty);
        // pthread_exit(0);

        if(count == 0){
            printf("Consumer consumed %d Buffer Empty\n", buffer[out]);
        }
        else{
            printf("Consumer consumed %d buffer size = %d\n", buffer[out], count);
        }

        
    }
    pthread_exit(0);
}
