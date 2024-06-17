// title : peek_send.c
// date : 2024-06-17
// desc : MSG_PEEK & MSG_DONTWAIT 옵션 클라이언트

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 30
void error_handling(char * message);

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in send_adr;
	if(argc!=3){
		printf("Usage : %s <IP> <port> \n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&send_adr, 0, sizeof(send_adr));
	send_adr.sin_family = AF_INET;
	send_adr.sin_addr.s_addr = inet_addr(argv[1]);
	send_adr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&send_adr, sizeof(send_adr)) == -1)	// 연결요청 진행
		error_handling("connect() error!");

	write(sock, "123", strlen("123"));	// 문자열 123 전송
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
