//------------------------------------------------
// --実行結果--  スレッド間で、スタック領域のデータは共有しないという例
//main-1: varA=1, varB=2
//threadFunc -1-1; varA=1, varB=4
//threadFunc -1-2; varA=5, varB=4
//main-2: varA=5, varB=3
//threadFunc -2-1; varA=5, varB=8
//threadFunc -2-2; varA=10, varB=8
//threadFunc -1-3; varA=10, varB=4
//threadFunc -1-4; varA=10, varB=6
//threadFunc -2-3; varA=10, varB=8
//threadFunc -2-4; varA=10, varB=12
//main-3: varA=10, varB=3
//------------------------------------------------

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int varA; #ヒープ領域（多分正確には、データ領域）

void *threadFunc(void *arg) {
	int n = (int)arg;
	int varB;　#(スタック領域)

	varB = 4*n;
	printf("threadFunc -%d-1; varA=%d, varB=%d\n",n, varA, varB);
	varA = 5*n;
	printf("threadFunc -%d-2; varA=%d, varB=%d\n",n, varA, varB);
	sleep(2);
	printf("threadFunc -%d-3; varA=%d, varB=%d\n",n, varA, varB);
	varB = 6*n;
	printf("threadFunc -%d-4; varA=%d, varB=%d\n",n, varA, varB);

	return NULL;
}


int main(void){
	pthread_t thread1, thread2;

	int varB; #(スタック領域)

	varA = 1;
	varB = 2;
	printf("main-1: varA=%d, varB=%d\n", varA, varB);
	pthread_create(&thread1, NULL, threadFunc, (void *)1);
	sleep(1);
	varB = 3;
	printf("main-2: varA=%d, varB=%d\n", varA, varB);
	pthread_create(&thread2, NULL, threadFunc, (void *)2);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	printf("main-3: varA=%d, varB=%d\n", varA, varB);

	return 0;
}
