/* parent.c */
// Natthapong Lueangphumphitthaya 63011208
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[ ]){
  pid_t pid, w;
  int i, status;
  char value[3]; 
  
  int result = 0;

  for (i = 0; i < 2; ++i) {
    if ((pid = fork( )) == 0) {
      if(i == 1){
        execl("child", "child", argv[1], argv[2],  NULL);
      }
      else{
        execl("child", "child", argv[3], argv[4],  NULL);
      }
    }
  }
/*	Wait for the children				
*/

  while ((w = wait(&status)) && w != -1) {
 	    printf("Wait on PID: %d returns status of : %d\n", w, 
			result += WEXITSTATUS(status));
  }

  printf("Result: %d\n", result);

  exit(0);
}

