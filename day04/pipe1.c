// title : pipe1.c
// date : 2024-06-14
// desc : 파이프 기반의 프로세스 간 통신

#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
	int fds[2];
	char str[] = "Who are you?";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds);	// pipe 함수 호출을 통해 파이프를 생성
	pid=fork();	// 파이프는 복사되지 않고 파이프 입출력에 사용되는 파일 디스크립터 복사
	if(pid == 0)
	{
		write(fds[1], str, sizeof(str));	// 파이프로 문자열 전달
	}
	else
	{
		read(fds[0], buf, BUF_SIZE);		// 파이프로 부터 문자열 수신
		puts(buf);
	}
	return 0;
}
