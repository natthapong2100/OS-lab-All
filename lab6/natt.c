#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

static int received = 0;
pid_t pid[5],arr[5]; 
int i,child_status;
pid_t pidChildArr[5];

void sigterm_handler(int signum){
    // printf("In sig term handler\n");
     if(signum == SIGTERM){
        received = 1;
     } 
}


int main(){
    signal(SIGTERM, sigterm_handler);
    for(i = 0; i < 5; i++){
        pid[i]=fork();

        if (pid[i]== -1){
            return 1;
        }
        if(pid[i]==0){
            printf("Child: my id is %d\n",getpid());
            pidChildArr[i] = getpid();
            while(!received);
        } 
        else{
            sleep(2);
            //killing process
            kill(pidChildArr[i], SIGTERM); 
            printf("Child: my id is %d, my parent has just terminated me\n",getpid());
            exit(0);
        }   
    }
    printf("Parent: I have killed all of my children\n");
    return 0;
}