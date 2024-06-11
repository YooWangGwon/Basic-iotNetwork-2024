// title : inet_addr.c
// date : 2024-06-11
// desc : inet_addr 함수

#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	char *addr1="1.2.3.4";
	char *addr2="1.2.3.256";	// 1바이트 당 최대크기 정수는 255이므로 잘못된 IP주소
								// inet_addr 함수의 오류 검출 능력 확인
	unsigned long conv_addr = inet_addr(addr1);
	if(conv_addr == INADDR_NONE)	// 정상 변환
		printf("Error occured! \n");
	else
		printf("Network ordered integer addr: %#lx \n", conv_addr);

	conv_addr = inet_addr(addr2);	// 오류 발생(INADDR_NONE 반환)
	if(conv_addr == INADDR_NONE)
		printf("Error occured! \n");
	else
		printf("Networked ordered integer adder : %#lx \n\n", conv_addr);
	return 0;
}
