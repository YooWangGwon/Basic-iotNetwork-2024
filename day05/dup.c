// title : dup.c
// date : 2024-06-17
// desc : dup 함수

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int cfd1, cfd2;
	char str1[] = "Hi~ \n";
	char str2[] = "It's a nice day~ \n";

	cfd1 = dup(1);	// dup 함수호출을 통해 파일 디스크립터 1(표준출력)을 복사
	cfd2 = dup2(cfd1, 7);	// dup2 함수호출을 통해서 복사한 파일디스크립터를 재복사

	printf("fd1=%d, fd2=%d \n", cfd1, cfd2);
	write(cfd1, str1, sizeof(str1));	// 복사된 파일 디스크립터를 이용해서 출력을 진행
	write(cfd2, str2, sizeof(str2));	// 위와 동일

	close(cfd1);	// 복사된 파일 디스크립터를 모두 종료
	close(cfd2);
	write(1, str1, sizeof(str1));
	close(1);	// 마지막 파일 디스크립터를 종료
	write(1, str2, sizeof(str2));	// 파일 디스크립터가 종료되어 출력 안됨
	return 0;
}
