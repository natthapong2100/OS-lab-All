// OS Lab 6 Q 1
// Natthapong Lueangphumphitthaya 63011208

#include  <stdio.h>
#include  <signal.h>
#include <stdlib.h>
#include <unistd.h>
#define clear_buffer() while(getchar() != '\n') 

void TERMhandler(int);               /* Ctrl-C handler           */
pid_t pidChildArr[5];

void  main(void)
{
    // signal(SIGINT, TERMhandler);         /* install Ctrl-C handler   */

    pid_t pid;
    int i;

    for(int i = 0; i < 5; i++){
        pid = fork();
        signal(SIGTERM, TERMhandler); 

        // printf("Child: my id is %d\n", getpid());
        // pidChildArr[i] = getpid();

        if(pid == 0){

            // printf("Enter looping..\n");
            printf("Child: my id is %d\n", getpid());
            pidChildArr[i] = getpid();
            while(1);
            // printf("Child: my id is %d, my parent has just terminated me\n", getpid());
            
        }
        // else{
        //     sleep(2);
        //     // wait(NULL);
        //     printf("Child: my id is %d, my parent has just terminated me\n", pidChildArr[i]);
        //     // kill(pidChildArr[i], SIGTERM);
        // }
        sleep(2);
        // kill(pid, SIGTERM);
        // wait(NULL);
        printf("Child: my id is %d, my parent has just terminated me\n", getpid());
        // kill(pidChildArr[i], SIGTERM);
    }
    printf("Parent: I have killed all of my children\n");
    
}

void  TERMhandler(int sig)
{
    // printf("in term handler\n");
    // kill(pidChildArr, SIGTERM);
    for(int i = 0; i < 5; i++){
        kill(getpid(), SIGTERM);
    }
    signal(SIGTERM, TERMhandler); 
}

// gcc -o q2 q2.c
