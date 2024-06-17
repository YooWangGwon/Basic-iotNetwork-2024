// title : readv.c
// date : 2024-06-17
// desc : readv 함수

#include <stdio.h>
#include <sys/uio.h>
#define BUF_SIZE 100

int main(int argc, char *argv[])
{
	struct iovec vec[2];
	char buf1[BUF_SIZE] = {0,};
	char buf2[BUF_SIZE] = {0,};
	int str_len;

	vec[0].iov_base = buf1;	// 첫번째 데이터 저장소의 위치
	vec[0].iov_len = 5;		// 저장할 데이터의 크기 정보
	vec[1].iov_base = buf2;		// 두번째 데이터 저장소의 위치
	vec[1].iov_len = BUF_SIZE;	//	저장할 데이터의 크기 정보

	str_len = readv(0, vec, 2);	// 데이터 수신할 파일(소켓)의 파일 디스크립터가 0이므로 콘솔로 부터 데이터 수신
	printf("Read bytes : %d \n", str_len);
	printf("First Message : %s \n", buf1);
	printf("Second Message : %s \n", buf2);
	return 0;
}
