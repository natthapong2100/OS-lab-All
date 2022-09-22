/* child.c */
// Natthapong Lueangphumphitthaya 63011208
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[ ]){
	int num1, num2, result;
	num1 = atoi(argv[1]);
	num2 = atoi(argv[2]);
	result = num1 + num2;
	exit(result);
}
