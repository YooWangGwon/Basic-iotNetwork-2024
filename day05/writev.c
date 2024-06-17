// title : writev.c
// date : 2024-06-17
// desc : writev.c 함수

#include <stdio.h>
#include <sys/uio.h>

int main(int argc, char *argv[])
{
	struct iovec vec[2];
	char buf1[] = "ABCDEFG";
	char buf2[] = "1234567";
	int str_len;

	vec[0].iov_base = buf1;		// 첫번째로 전송할 데이터의 저장 위치
	vec[0].iov_len = 3;			// 첫번째로 전송할 데이터의 크기 정보
	vec[1].iov_base = buf2;		// 두번째로 전송할 데이터의 저장 위치
	vec[1].iov_len = 4;			// 두번째로 전송할 데이터의 크기 정보

	str_len = writev(1, vec, 2);// 데이터 전송 목적지의 파일 디스크립터가 1이므로 콘솔에 출력
	puts("");
	printf("Write bytes: %d \n", str_len);
	return 0;
}
