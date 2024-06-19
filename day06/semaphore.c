#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void * read(void * arg);
void * accu(void * arg);
static sem_t sem_one;	// 세마포어 변수 선언 1
static sem_t sem_two;	// 세마포어 변수 선언 2
static int num;

int main(int argc, char *argv[])
{
	pthread_t id_t1, id_t2;
	sem_init(&sem_one, 0, 0);	// 세마포어 생성 1
	sem_init(&sem_two, 0, 1);	// 세마포어 생성 2

	pthread_create(&id_t1, NULL, read, NULL);
	pthread_create(&id_t2, NULL, accu, NULL);

	pthread_join(id_t1, NULL);
	pthread_join(id_t2, NULL);

	sem_destroy(&sem_one);
	sem_destroy(&sem_two);
	return 0;
}

void * read(void * arg)
{
	int i;
	for(i=0; i<5; i++)
	{
		fputs("Input num : ", stdout);

		sem_wait(&sem_two);	// sem_two를 이용한 wait 함수 호출
		scanf("%d", &num);	// accu를 호출하는 쓰레드가 값을 가져가지도 않았는데 read함수를 호출하는 쓰레드가 값을 다시 가져다 놓는 상황을 막기 위함
		sem_post(&sem_one);	// sem_one을 이용한 post 함수 호출
	}
	return NULL;
}
void * accu(void * arg)
{
	int sum = 0, i;
	for(i=0; i<5; i++)
	{
		sem_wait(&sem_one);	// sem_one을 이용한 wait 함수 호출 -> read 함수를 호출하는 쓰레드가 새로운 값을 가져다 놓기도 전에 accu 함수가 값을 가져가 버리는 상황
		sum += num;
		sem_post(&sem_two);	// sem_two를 이용한 post함수 호출
	}
	printf("Result: %d \n", sum);
	return NULL;
}
