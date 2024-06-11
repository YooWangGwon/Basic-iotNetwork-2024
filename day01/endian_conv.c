// title : endian_conv.c
// date : 2024-06-11
// desc : 바이트 순서 변환

#include<stdio.h>
#include<arpa/inet.h>

int main(int argc, char *argv[])
{
	unsigned short host_port = 0x1234;
	unsigned short net_port;
	unsigned long host_addr = 0x12345678;
	unsigned long net_addr;

	net_port = htons(host_port);	// 빅 엔디안으로 변환 1
	net_addr = htonl(host_addr);	// 빅 엔디안으로 변환 2

	printf("Host orderd port: %#x \n", host_port);
	printf("Network ordered port : %#x \n", net_port);
	printf("Host orderd address : %#x \n", host_addr);
	printf("Network ordered address : %#x \n", net_addr);
	return 0;
}
