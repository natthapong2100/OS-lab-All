// OS Lab 6 Q 1
// JIRAPAD SANGUANPAN 63011157

#include  <stdio.h>
#include  <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void INThandler(int);               /* Ctrl-C handler           */

void  main(void)
{
    pid_t pid, ppid;
    signal(SIGINT, INThandler);         /* install Ctrl-C handler   */

    printf("parent: Waiting for my child to send SIGINT\n");
    pid = fork();
    if(pid == 0){
        printf("child: Sleeping for 5 seconds\n");
        sleep(5);
        kill(getppid(), SIGINT);
        printf("child: Bye\n");
        exit(0);
    }
    while (1){  /* loop forever and wait    */
        pause();
    }

}

void  INThandler(int sig)
{
    printf("get SIGINT from child\n");
    printf("parent: Bye\n");
    exit(0);
}

