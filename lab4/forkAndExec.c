
// Natthapong Lueangphumphitthaya 63011208

/* forkAndExec.c */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
    pid_t pid;
    int choice;

    while(1){
        printf("\nChoice\n1. ls\n2. date\n3. ps\n0. exit\nYour Choice: ");
        scanf("%d", &choice);
        printf("\n");

        pid = fork();

        if (pid < 0) { /* error occurred */
            fprintf(stderr, "Fork Failed");
            exit(-1);
        }
        else if (pid == 0) { /* child process */

            if(choice == 0){
                exit(0);
            }
            else if(choice == 1){
                execlp("ls", "ls", NULL);
            }
            else if(choice == 2){
                execlp("date", "date", NULL);
            }
            else if(choice == 3){
                execlp("ps", "ps", NULL);
            }

        }
        else { /* parent process */
                /* parent will wait for the child to complete */
            wait (NULL);
            // exit(0); // don't need exit because it will go here every time and exit the program
        }

        if(choice == 0) exit(0);
        
    }
}
