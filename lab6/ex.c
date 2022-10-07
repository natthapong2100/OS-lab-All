// OS Lab 6 Q 1
// Natthapong Lueangphumphitthaya 63011208

#include  <stdio.h>
#include  <signal.h>
#include <stdlib.h>
#include <unistd.h>


void  main(void)
{
    pid_t child_pid = fork ();
    printf ("Process %d is running\n", getpid ());

    /* Exit if the fork fails to create a process */
    if (child_pid < 0)
        exit (1);

    /* The child enters an infinite loop */
    if (child_pid == 0)
        while (1) ;

    /* Make the parent sleep so the child gets a chance to run */
    sleep (1);
    /* The parent sends the SIGKILL signal to kill the child */
    kill (child_pid, SIGKILL);
    printf ("Process %d is exiting\n", getpid ());
    
}

