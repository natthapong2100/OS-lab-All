#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
 
// 63011402 Chatchai Paisalpanich 
// 2022 Oct 20 
// Lab 8 Q1
 
const int BUFFER_SIZE = 5;
int MY_BUFFER[5] = {-1,-1,-1,-1,-1};
 
sem_t mutex; // Semaphore called mutex which is a jar with 1 marble inside it
sem_t full_jar; 
sem_t empty_jar; 
 
void *insertbuffer(void *param);
void *removebuffer(void *param);
 
int main() {
    pthread_t tid1, tid2; // Thread id 
    pthread_attr_t attr; // Thread attributes 
 
    pthread_attr_init(&attr);
 
    sem_init(&mutex, 0,1); // initialize mutex semaphore with 1 marble in it
    sem_init(&full_jar, 0, 0); // Semaphore called full_jar which is a jar which will have 0 marbles in it at first
    sem_init(&empty_jar, 0, 5); // Initialize semaphone called empty_jar which is a jar with 5 marbles in it at first
 
    pthread_create(&tid1, &attr, insertbuffer, NULL);
    pthread_create(&tid2, &attr, removebuffer, NULL);
 
    /* now wait for the thread to exit */
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
 
    sem_destroy(&mutex);
    sem_destroy(&full_jar);
    sem_destroy(&empty_jar);
}
 
void *insertbuffer (void *param) {
 
    int produceIndex = 0;
 
    for(int i = 0; i < 40; i++){
 
        sem_wait(&empty_jar); // "Hey there is a marble in empty_jar, produced can write to buffer"
        sem_wait(&mutex); // Produce see there is a marble in mutex, and takes out the marble
 
        // Inserting something onto the buffer
        int insert_value = i * 10;
        MY_BUFFER[produceIndex] = insert_value;
        produceIndex++;
        produceIndex = produceIndex % BUFFER_SIZE;
 
        printf("Produce entered product %d, produceIndex is %d \n", insert_value, produceIndex);
 
        sem_post(&mutex); // Producer puts back the marble into the mutex semaphore
        sem_post(&full_jar); // "Produce puts a marble in the semaphore full_jar"
    }
 
 
    pthread_exit(0);
}
 
void *removebuffer (void *param) {
 
    int consumeIndex = 0; 
 
    for(int i = 0; i < 40; i++){
 
        sem_wait(&full_jar); // Consumer see that there is a marble in the full_jar so took one marble out
        sem_wait(&mutex); // Consumer lock the buffer so producer can't produce while consumer is consuming
 
        int consumedProduct;
        consumedProduct = MY_BUFFER[consumeIndex];
        consumeIndex++;
        consumeIndex = consumeIndex % BUFFER_SIZE;
 
        printf("Consumer consumed %d, consumeIndex is %d \n", consumedProduct, consumeIndex);
 
        sem_post(&mutex); // Consumer unlock the buffer
        sem_post(&empty_jar); // Consumer put a marble into the empty_jar semaphore
    }
 
    pthread_exit(0);
}