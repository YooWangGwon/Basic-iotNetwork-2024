// title : thread1.c
// date : 2024-06-18
// desc : 쓰레드의 생성

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
void* thread_main(void *arg);

int main(int argc, char *argv[])
{
	pthread_t t_id;
	int thread_param = 5;

	if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0)	// thread_main 함수의 호출을 시작으로 별도의 실행흐름을 구성하는 쓰레드의 생성을 요청
	{
		puts("pthread_create() error");
		return -1;
	};
	sleep(10);	// sleep 함수를 통해서 main 함수의 실행을 10초간 중지시킴
	puts("end of main");
	return 0;
}

void* thread_main(void *arg)	// 매개변수 arg로 전달되는 것은  15행에서 호출한 pthread_create 함수의 네 번째 전달인자
{
	int i;
	int cnt = *((int*)arg);
	for(i=0; i<cnt; i++)
	{
		sleep(1);	// 2로 변경할 경우 다섯 번이 아닌 네번만 출력됨 -> 쓰레드가 정상종료 될수 있게 main 함수가 충분한 시간동안 기다려주어야 함
		puts("running thread");
	}
	return NULL;
}
