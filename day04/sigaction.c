// title : sigcaction.c
// date : 2024-06-14
// desc : sigaction 함수

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)
{
	if(sig == SIGALRM)
		puts("Time out!");
	alarm(2);
}

int main(int argc, char * argv[])
{
	int i;
	struct sigaction act;	// 시그널 발생시 호출될 함수의 등록을 위한 구조체 변수 선언
	act.sa_handler = timeout;	// 구조체의 sa_handler에 함수 포인터 값 지정
	sigemptyset(&act.sa_mask);	// sa_mask의 모든 비트를 0으로 초기화
	act.sa_flags = 0;			// signal 함수를 대신하기 위해 필요한 멤버가 아니므로 0으로 초기화
	sigaction(SIGALRM, &act, 0);	// 시그널 SIGALRM에 대한 핸들러 지정

	alarm(2);	// 2초 뒤 SIGALRM 시그널 발생 예약

	for(i=0; i<3; i++)
	{
		puts("wait...");
		sleep(100);
	}
	return 0;
}
