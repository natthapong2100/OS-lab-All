/* forkExample.c */
// Natthapong Lueangphumphitthaya 63011208
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
  pid_t pid;
  int i;
  printf("One of the possible outputs is\n");
  for (int i = 0; i < 5; i++) {
    pid = fork();
    if (pid == 0) { // child (we consider)
        if (i%2 == 0 ) { // even num
            for(int j = 0; j < 4; j++){
                pid = fork(); // fork again
                if(pid == 0){ // when folk u will get the value that more than 0, but child always 0 we need it
                    printf("I am sub-child %d of child %d\n", j, i);
                    exit(0);
                    
                }
                
            }
        }
        else{ // if it's odd
            for(int j = 0; j < 5; j++){
                pid = fork(); // fork again
                if(pid == 0){
                    printf("I am sub-child %d of child %d\n", j, i);
                    exit(0);
                }
            }
        }
    //    printf("child i = %d\n", i);
       printf("I am child %d\n", i);
       exit(0);
    }
    
  }
  printf("I am parent\n");

  return 0;
}