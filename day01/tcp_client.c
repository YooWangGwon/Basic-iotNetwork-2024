// title : tcp_client.c
// date : 2024-06-11
// desc : TCP 소켓 클라이언트

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char *message);

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len = 0;
	int idx = 0, read_len = 0;

	if(argc != 3){
		printf("Usage : %s <IP> <port> \n", argv[0]);
		exit(1);
	}

	sock=socket(PF_INET, SOCK_STREAM, 0);
	// TCP 소켓 생성. PF_INET, SOCK_STREAM을 인자로 전달하여
	// 세번째 인자인 IPPROTO_TCP는 생략 가능
	if(sock == -1)
		error_handling("socket() error");
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error!");

	while(read_len = read(sock, &message[idx++], 1))
	// while문 안에서 read함수를 반복 호출 -> 호출될 때마다 1바이트씩 데이터를 읽음
	{
		if(read_len == -1)
			error_handling("read() error!");
		// read_len에 저장되어 있는 값은 항상 1
		str_len += read_len;
	}

	printf("Message from server: %s \n", message);
	printf("Function read call count: %d \n", str_len);
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
