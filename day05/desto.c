// title : desto.c
// date : 2024-06-17
// desc : fdopen 함수를 이용한 FILE 구조체 포인터로의 변환

#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	FILE *fp;
	int fd = open("data.dat", O_WRONLY|O_CREAT|O_TRUNC);	// open 함수를 사용하여 파일 디스크립터 반환
	if(fd == -1)
	{
		fputs("file open error", stdout);
		return -1;
	}

	fp = fdopen(fd, "w");	// 모드 "w"인 fdopen 함수 호출로 출력모드의 FILE포인터가 반환됨
	fputs("Network C Programming \n", fp);	// 위에서 얻은 포인터를 기반으로 표준출력 함수 fputs 함수 호출
	fclose(fp);	// 파일 포인터를 이용하여 파일 닫기(파일 자체가 완전 종료 되므로 파일 디스크립터를 이용해서 또 다시 종료할 필요 없음

	return 0;
}
