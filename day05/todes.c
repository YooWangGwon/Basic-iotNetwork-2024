// title : todes.c
// date : 2024-06-17
// desc : fileno를 이용한 파일 디스크립터 변환


#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	FILE *fp;
	int fd = open("data.dat", O_WRONLY|O_CREAT|O_TRUNC);
	if(fd == -1)
	{
		fputs("file open error", stdout);
		return -1;
	}

	printf("First file descriptor : %d \n", fd);	// 12행에서 반환된 파일 디스크립터으 ㅣ정수 값 출력
	fp = fdopen(fd, "w");	// fdopen 함수 호출을 통해서 파일 디스크립터를 FILE 포인터로
	fputs("TCP/IP SOCKET Programming \n", fp);
	printf("Second file descriptor : %d \n", fileno(fp));	// fileno 함수 호출을 통해서 포인터를 다시 파일 디스크립터로 변환
	fclose(fp);
	return 0;
}
