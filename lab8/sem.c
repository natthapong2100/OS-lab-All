// OS Lab 7 Q 1
// Natthapong Lueangphumphitthaya 63011208

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
 
const int BUFFER_SIZE = 5;
int buffer[5] = {-1,-1,-1,-1,-1};
 
sem_t *mutex;
sem_t *full_jar; 
sem_t *empty_jar; 
 
void *insertBuffer(void *param);
void *removeBuffer(void *param);
 
int main() {
    pthread_t tid1, tid2; 
    pthread_attr_t attr; 
 
    pthread_attr_init(&attr);
 
    mutex = sem_open("/semaphore", O_CREAT, 0666, 1);
    full_jar = sem_open("/fully_sem", O_CREAT, 0666, 0);
    empty_jar = sem_open("/empty_sem", O_CREAT, 0666, BUFFER_SIZE);

    pthread_create(&tid1, &attr, insertBuffer, NULL);
    pthread_create(&tid2, &attr, removeBuffer, NULL);
 
    /* now wait for the thread to exit */
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
 
    sem_close(mutex);
    sem_unlink("/semaphore");
    sem_close(full_jar);
    sem_unlink("/fully_sem");
    sem_close(empty_jar);
    sem_unlink("/empty_sem");
}
 
void *insertBuffer (void *param) {
 
    int in = 0;
 
    for(int i = 0; i < 40; i++){
        sem_wait(empty_jar);
        sem_wait(mutex);
 
        // insert value to buffer
        int insert_value = i;
        buffer[in] = insert_value;
        in++;
        in = in % BUFFER_SIZE;

        if(in == 0){
            printf("Produce Entered %d Buffer Full\n", insert_value);
        }
        else{
            printf("Produce Entered %d Buffer size = %d\n", insert_value, in);
        }
 
        sem_post(mutex);
        sem_post(full_jar);
    }
 
 
    pthread_exit(0);
}
 
void *removeBuffer (void *param) {
 
    int out = 0;
    int size = 5;
    for(int i = 0; i < 40; i++){
 
        sem_wait(full_jar); 
        sem_wait(mutex);

        int consume_value = buffer[out];
        out++;
        out = out % BUFFER_SIZE;
        size = (size - 1) % BUFFER_SIZE;


        if(size == 0){
            printf("Consumer consumed %d Buffer Empty\n", consume_value);
            size = 5;
        }
        else{
            printf("Consumer consumed %d buffer size = %d \n", consume_value, size);
        }
        
 
        sem_post(mutex); 
        sem_post(empty_jar); 
    }
 
    pthread_exit(0);
}