#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t pid;
    int inp = 1000;

    while(1){
        printf("1.\tls\n2.\tdate\n3.\tps.\n0.\texit\nInput: ");
        scanf("%d", &inp);
        printf("\n");
        
        pid = fork();
        if (pid < 0) { /* error motherfcker */
            fprintf(stderr, "Fork Failed");
            exit(-1);
        }
        else if (pid == 0) { /* child process */
            switch(inp){
                case 1:
                    execlp("/bin/ls", "ls", NULL); //execlp executes from the home folder
                    break;
                case 2:
                    execlp("/bin/date", "date", NULL);
                    break;
                case 3:
                    execlp("/bin/ps", "ps", NULL);
                    break;
                case 0:
                    exit(0); //exit child process
                default:
                    break;
            }
        }
        else { /* parent process - wait until child complete */
            wait (NULL);
        }
        
        if(inp == 0) exit(0); //exit parent process
        printf("\n");
    }

}