// OS Lab 7 Q 1
// Natthapong Lueangphumphitthaya 63011208

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define SIZE 1024

int main(int argc, char **argv)
{
  int pfd[2];
  int nread;
  int pid;
  char buf[SIZE];
  int sum;

  if (pipe(pfd) == -1)
  {
    perror("pipe failed");
    exit(1);
  }
  if ((pid = fork()) < 0)
  {
    perror("fork failed");
    exit(2);
  }

  if (pid == 0)
  {
        /* child */

        close(pfd[0]);
        printf("Child: I am calculating\n");
        int upper = atoi(argv[1]);

        for(int i = 0; i <= upper; i++){
            sum += i;
        }
        printf("Child: the result is %d\n", sum);
        sprintf(buf, "%d", sum); // convert to buf(char type)
        write(pfd[1], buf, strlen(buf)+1);

        printf("Child: I am sending data\n");
        printf("Child: Goodbye\n");

        close(pfd[1]);
  } else {
        /* parent */

        close(pfd[1]);
        printf("Parent: waiting for my child\n");

        while ((nread = read(pfd[0], buf, SIZE)) != 0) 
            printf("Parent: sum from my child is %s\n", buf);

        printf("Parent: Goodbye\n");

        close(pfd[0]); // 0 = read, 1 = write ********
        wait(NULL);
  }
  exit(0);
}

// gcc -o q1 q1.c