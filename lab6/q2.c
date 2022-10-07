// OS Lab 6 Q 2
// JIRAPAD SANGUANPAN 63011157

#include  <stdio.h>
#include  <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void TERMhandler(int);

void  main(void)
{
    pid_t pid, ppid;
    int pidChildArr[5];
    signal(SIGTERM, TERMhandler);

    for(int i = 0; i < 5; i++){
        pid = fork();
        pidChildArr[i] = pid;

        if(pid == 0){
            printf("Child: my id is %d\n", getpid());
            while(1);
        }
    }

    sleep(2);
    
    for(int i = 0; i < 5; i++){
        kill(pidChildArr[i], SIGTERM);
    }
    while(wait(NULL) != -1);
    printf("Parent: I have killed all of my children\n");
    
}

void  TERMhandler(int sig)
{
    printf("Child: my id is %d, my parent has just terminated me\n", getpid());
    exit(0);
}
