// title : mutex.c
// date : 2024-06-18
// desc : 뮤텍스

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#define NUM_THREAD 100

void * thread_inc(void * arg);
void * thread_des(void * arg);
long long num = 0;
pthread_mutex_t mutex;	// 뮤텍스 참조값 저장을 위한 전역 변수 선언

int main(int argc, char *argv[])
{
	pthread_t thread_id[NUM_THREAD];
	int i;

	pthread_mutex_init(&mutex, NULL);	// 뮤텍스를 초기화

	for( i=0; i<NUM_THREAD; i++)
	{
		if(i%2)
			pthread_create(&(thread_id[i]),NULL,thread_inc, NULL);
		else
			pthread_create(&(thread_id[i]),NULL,thread_des, NULL);
	}

	for(i=0;i<NUM_THREAD;i++)
		pthread_join(thread_id[i], NULL);


	printf("result: %lld \n", num);
	pthread_mutex_destroy(&mutex);	// 뮤텍스의 소멸
	return 0;
}

void * thread_inc(void * arg)
{
	int i;
	pthread_mutex_lock(&mutex);
	for(i=0; i<50000000;i++)
		num += 1;				// 실질적인 임계영역 1
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void * thread_des(void * arg)
{
	int i;
	for(i=0; i<50000000;i++)
	{
		pthread_mutex_lock(&mutex);
		num -= 1;				// 실질적인 임계영역 2
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
