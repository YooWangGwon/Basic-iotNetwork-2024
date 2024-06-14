// title : signal.c
// date : 2024-06-14
// desc : signal 함수

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)	// 시그널이 발생했을 때 호출되어야 할 함수 -> 시그널 핸들러 1
{
	if(sig==SIGALRM)
		puts("Time out!");
	alarm(2);	// 2초 간격으로 SIGALRM 시그널을 반복 발생시키기 위해 시그널 핸들러 함수 내에서 alarm 함수 호출
}

void keycontrol(int sig)	// 시그널 핸들러 2
{
	if(sig==SIGINT)
		puts("CTRL + C pressed");
}

int main(int argc, char *argv[])
{
	int i;
	signal(SIGALRM, timeout);		// 시그널 SIGALRM에 대한 시그널 핸들러 timeout 등록
	signal(SIGINT, keycontrol);		// 시그널 SIGINT에 대한 시그널 핸들러 keycontorl 등록
	alarm(2);		// 시그널 SIGALRM의 발생을 2초 뒤로 예약

	for(i = 0; i<3; i++)
	{
		puts("wait...");
		sleep(100);
	}
	return 0;
}
