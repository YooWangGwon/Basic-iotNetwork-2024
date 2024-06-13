// title : fork.c
// date : 2024-06-13
// desc : fork함수 연습

#include <stdio.h>
#include <unistd.h>

int gval = 10;
int main (int argc, char *argv[])
{
	pid_t pid;
	int lval = 20;
	gval++, lval += 5;

	pid = fork();	// 부모 프로세스 : 자식 프로세스 PID, 자식 프로세스 : 0

	if(pid == 0)
		gval += 2, lval += 2;	// 자식 프로세스 실행
	else
		gval -= 2, lval -= 2;	// 부모 프로세스 실행

	if(pid == 0)
		printf("Child Proc : [%d, %d] \n", gval, lval);		// 자식 프로세스 실행
	else
		printf("Parent Proc : [%d, %d] \n", gval, lval);	// 부모 프로세스 실행

	return 0;
}
