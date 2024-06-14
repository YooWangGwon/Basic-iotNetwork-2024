// title : wait.c
// date : 2024-06-14
// desc : wait 함수

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[])
{
	int status;
	pid_t pid = fork();	// 자식프로세스 생성

	if(pid == 0)
	{
		return 3;	// 13행에서 생성된 자식 프로세스 실행 종료
	}
	else
	{
		printf("Child PID : %d \n", pid);
		pid=fork();		// 자식 프로세스 생성
		if(pid == 0)
		{
			exit(7);	// 22행에서 생성된 자식프로세스 실행 종료
		}
		else
		{
			printf("Child PID : %d \n");
			wait(&status);	// 종료된 프로세스 관련 정보가 status에 담겨지고, 해당 정보의 프로세스는 완전히 소멸
			if(WIFEXITED(status))	// 자식 프로세스의 정상 종료 여부를 확인
				printf("Child send one: %d \n", WEXITSTATUS(status));	// 정상종료된 경우 자식 프로세스가 전달한 값을 출력

			wait(&status);	// 앞서 생성한 자식 프로세스가 2개 이므로 또 한번의 wait 함수 사용
			if(WIFEXITED(status))
				printf("Child send one: %d \n", WEXITSTATUS(status));
			sleep(30); // Sleep 30sec
		}
	}
	return 0;
}
