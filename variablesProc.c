//--
//  --実行結果--
//  main-1: varA=1, varB=2
//  processFunc -1-1; varA=1, varB=4
//  processFunc -1-2; varA=5, varB=4
//  main-2: varA=1, varB=3
//  processFunc -2-1; varA=1, varB=8
//  processFunc -2-2; varA=10, varB=8
//  processFunc -1-3; varA=5, varB=4
//  processFunc -1-4; varA=5, varB=6
//  processFunc -2-3; varA=10, varB=8
//  processFunc -2-4; varA=10, varB=12
//  main-3: varA=1, varB=3
//--
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int varA; 

void processFunc(int n) {
	int varB;

	varB = 4*n;
	printf("processFunc -%d-1; varA=%d, varB=%d\n",n, varA, varB);
	varA = 5*n;
	printf("processFunc -%d-2; varA=%d, varB=%d\n",n, varA, varB);
	sleep(2);
	printf("processFunc -%d-3; varA=%d, varB=%d\n",n, varA, varB);
	varB = 6*n;
	printf("processFunc -%d-4; varA=%d, varB=%d\n",n, varA, varB);

	exit(0);
}


int main(void){
	pid_t process1, process2;
	int varB; 
	varA = 1;
	varB = 2;
	printf("main-1: varA=%d, varB=%d\n", varA, varB);
	if((process1 = fork()) == 0){
		// this is child process
		processFunc(1);
	}
	sleep(1);
	varB = 3;
	printf("main-2: varA=%d, varB=%d\n", varA, varB);
	if((process2 = fork()) == 0){
		// this is child process
		processFunc(2);
	}
	waitpid(process1,NULL,0);
	waitpid(process2,NULL,0);
	printf("main-3: varA=%d, varB=%d\n", varA, varB);

	return 0;
}
