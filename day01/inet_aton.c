// title : inet_aton.c
// date : 2024-06-11
// desc : inet_aton함수

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
	char *addr = "127.232.124.79";
	struct sockaddr_in addr_inet;	// 변환된 IP 주소 정보를 담을 sockaddr_in 구조체

	if(!inet_aton(addr, &addr_inet.sin_addr))	// 별도로 구조체에 담는 과정 필요X
		error_handling("Conversion error");
	else
		printf("Network ordered integer addr: %#x \n",
			addr_inet.sin_addr.s_addr);	// 구조체의 멤버인 addr_in에 담겨있는 IP주소 출력
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
