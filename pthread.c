
// OS Lab 5 Q2
// Natthapong Lueangphumphitthaya 63011208

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int childSum; /* this data is shared by the thread(s) */
void *runner(void *param);

int main(int argc, char *argv[]) {
	pthread_t tid;
	pthread_attr_t attr;
	
	if (argc != 2) { // this allow (argc == 2) only to run this program
		fprintf(stderr, "usage: pthread <integer value>\n");
		exit(1);
	}
	if (atoi(argv[1]) < 0) {
		fprintf(stderr, "number must be >=0\n");
		exit(2);
	}
	/* each thread has a set of attributes including stack size
	   and scheduling information .
		In this example, we will not set the information, therefore,
	   we use the default attributes */ 
	/* get the default attributes */
	pthread_attr_init(&attr);
	/* create the thread */
	pthread_create(&tid, &attr, runner, argv[1]);
	/* now wait for the thread to exit */
	printf("I am mother thread, I will wait for my child thread\n"); // WAIT for child thread
	pthread_join(tid, NULL);
	printf("from my child sum = %d\n", childSum);

	printf("\nStart calculating Parent thread\n");
	int parentSum = 0;
	int num = atoi(argv[1]);
	for (int i = 0; i <= num; ++i) {
		parentSum += i;
	}
	printf("from my parent sum = %d\n", parentSum);
	printf("The final result: %d\n", (parentSum + childSum));

}

/* the thread will begin control in this function */
void *runner (void *param) {
	int i;
	int upper = atoi(param); // str -> int
	childSum = 0;
	printf("I am child thread, I am calculating\n");
	if (upper > 0) {
		for (i = 0; i <= (upper * 2); ++i) {
			childSum += i;
		}
	}
	pthread_exit(0); // use 0 or NULL
}

