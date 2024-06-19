// title : thread2.c
// date : 2024-06-18
// desc : 쓰레드의 조인

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
void* thread_main(void *arg);

int main(int argc, char *argv[])
{
	pthread_t t_id;
	int thread_param = 5;
	void * thr_ret;

	if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0)	// thread_main 함수의 호출을 시작으로 별도의 실행흐름을 구성하는 쓰레드의 생성을 요청
	{
		puts("pthread_create() error");
		return -1;
	};

	if(pthread_join(t_id, &thr_ret)!=0)	// 18행에서 생성된 쓰레드를 대상으로 pthread_join 함수를 호출
	{									// 변수 t_id에 저장된 ID의 쓰레드가 종료될 때 까지 대기함
		puts("pthread_join() error");
		return -1;
	}

	printf("Thread return message : %s \n", (char*)thr_ret);
	free(thr_ret);
	return 0;
}

void* thread_main(void *arg)	// 매개변수 arg로 전달되는 것은  15행에서 호출한 pthread_create 함수의 네 번째 전달인자
{
	int i;
	int cnt = *((int*)arg);
	char * msg = (char *)malloc(sizeof(char)*50);
	strcpy(msg, "Hello, I am thread~ \n");
	for(i=0; i<cnt; i++)
	{
		sleep(1);	// 2로 변경할 경우 다섯 번이 아닌 네번만 출력됨 -> 쓰레드가 정상종료 될수 있게 main 함수가 충분한 시간동안 기다려주어야 함
		puts("running thread");
	}
	return (void*)msg;
}
