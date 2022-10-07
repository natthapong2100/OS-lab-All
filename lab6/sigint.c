// OS Lab 6 Q 1
// Natthapong Lueangphumphitthaya 63011208

#include  <stdio.h>
#include  <signal.h>
#include <stdlib.h>
#include <unistd.h>
#define clear_buffer() while(getchar() != '\n') 

void INThandler(int);               /* Ctrl-C handler           */

void  main(void)
{
    signal(SIGINT, INThandler);         /* install Ctrl-C handler   */

    printf("parent: Waiting for my child to send SIGINT\n");
    while (1){  /* loop forever and wait    */
        printf("child: Sleeping for 5 seconds\n");
        sleep(5);
        printf("get SIGINT from child\n");
        exit(0);
    }

    printf("parent: Bye\n");

}

void  INThandler(int sig)
{
    printf("child: sending SIGINT\n");
    kill(getppid(), sig);
    printf("child: Bye\n");

}

// gcc -o sigint sigint.c
