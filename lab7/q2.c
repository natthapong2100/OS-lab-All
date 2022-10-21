// OS Lab 7 Q 2
// Natthapong Lueangphumphitthaya 63011208

#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

void  ClientProcess(int []);

void  main(int  argc, char *argv[])
{
     int    ShmID;
     int    *ShmPTR;
     pid_t  pid;
     int    status;
     
     if (argc != 2) {
          printf("Use: %s #1\n", argv[0]);
          exit(1);
     }
     
     ShmID = shmget(IPC_PRIVATE, 1*sizeof(int), IPC_CREAT | 0666); // old = 4, in this func() -> size of int = 4 bytes
     if (ShmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     printf("Parent: I have created a shared memory for result...\n"); // o/p begin
     
     ShmPTR = (int *) shmat(ShmID, NULL, 0);
     if ( ShmPTR == NULL) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
     printf("Parent: I have attached the shared memory...\n"); 
     
     ShmPTR[0] = atoi(argv[1]);
    //  ShmPTR[1] = atoi(argv[2]);
    //  ShmPTR[2] = atoi(argv[3]);
    //  ShmPTR[3] = atoi(argv[4]);

    //  printf("Server has filled %d %d %d %d in shared memory...\n",
    //         ShmPTR[0], ShmPTR[1], ShmPTR[2], ShmPTR[3]);
            
     printf("Parent: I am about to fork a child process...\n");
     pid = fork();
     if (pid < 0) {
          printf("*** fork error (server) ***\n");
          exit(1);
     }
     else if (pid == 0) {
          ClientProcess(ShmPTR);
          exit(0);
     }

     printf("Parent: Waiting for my child\n"); // NEW ***
     wait(&status);

     printf("Parent: sum from my child is %d\n", ShmPTR[0]);
     shmdt((void *) ShmPTR);
     printf("Parent: I have detached the shared memory...\n");
     shmctl(ShmID, IPC_RMID, NULL);
     printf("Parent: I have removed the shared memory...\n");

     printf("Parent: Goodbye\n");
     exit(0);
}

void  ClientProcess(int  SharedMem[]) // ตรงนี้เปน child คำนวนตรงนี้ แล้วให้ parent เปนตัวแสดงผล
{
    printf("Child: I am calculating\n");

    // calculate
    int sum = 0;
    int upper_bound = SharedMem[0];
    for(int i = 0; i <= upper_bound; i++){
        sum += i;
    }
    SharedMem[0] = sum;
    printf("Child: The result is %d\n", SharedMem[0]);
    printf("Child: Goodbye\n");
}

// gcc -o q2 q2.c
