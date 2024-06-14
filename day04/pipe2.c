// title : pipe3.c
// date : 2024-06-14
// desc : 파이프 기반의 프로세스 간 양방향 통신

#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
	int fds1[2], fds2[2];
	char str1[] = "Who are you?";
	char str2[] = "Thank you for your message";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds1), pipe(fds2);	// pipe 함수 호출을 통해 파이프를 2개 생성
	pid=fork();	// 파이프는 복사되지 않고 파이프 입출력에 사용되는 파일 디스크립터 복사
	if(pid == 0)
	{
		write(fds1[1], str1, sizeof(str1));	// 파이프로 문자열 전달
		read(fds2[0], buf, BUF_SIZE);
		printf("Child proc output: %s \n", buf);

	}
	else
	{
		read(fds1[0], buf, BUF_SIZE);		// 파이프로 부터 문자열 수신
		printf("Parent proc output : %s \n", buf);
		write(fds2[1], str2, sizeof(str2));
		sleep(3);
	}
	return 0;
}
