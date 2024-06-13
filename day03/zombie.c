// title : zombie.c
// date : 2024-06-13
// desc : 좀비 프로세스 생성

#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv)
{
	pid_t pid = fork();

	if(pid == 0) // if Child Process
	{
		puts("Hi, I am a Child process.");
	}
	else
	{
		printf("Child Process ID : %d \n", pid);
		sleep(30);	//  sleep 30 sec
	}

	if(pid == 0)
		puts("End child process");
	else
		puts("End parent process");

	return 0;
}
