// title : peek_recv.c
// date : 2024-06-17
// desc : MSG_PEEK & MSG_DONTWAIT 옵션 서버

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int acpt_sock, recv_sock;
	struct sockaddr_in recv_adr, acpt_adr;
	int str_len, state;
	socklen_t recv_adr_sz;
	char buf[BUF_SIZE];

	if(argc != 2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	acpt_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&acpt_adr, 0, sizeof(acpt_adr));
	acpt_adr.sin_family = AF_INET;
	acpt_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	acpt_adr.sin_port = htons(atoi(argv[1]));

	if(bind(acpt_sock, (struct sockaddr*)&acpt_adr, sizeof(acpt_adr)) == -1)
		error_handling("bind() error!");
	listen(acpt_sock, 5);

	recv_adr_sz = sizeof(recv_adr);
	recv_sock = accept(acpt_sock, (struct sockaddr*)&recv_adr, &recv_adr_sz);

	while(1)
	{
		str_len = recv(recv_sock, buf, sizeof(buf)-1, MSG_PEEK|MSG_DONTWAIT);	// MSG_DONTWAIT : 데이터가 존재하지 않아도 블로킹 상태에 두지 않기 위함
		if(str_len > 0)
			break;
	}

	buf[str_len] = 0;
	printf("Buffering %d bytes : %s \n", str_len, buf);

	str_len = recv(recv_sock, buf, sizeof(buf)-1, 0);	// 이번 recv에서는 아무런 옵션도 설정하지 않아 읽어 들인 데이터가 입력버퍼에서 지워짐
	buf[str_len] = 0;
	printf("Read again : %s \n", buf);	// 한번밖에 전송되지 않은 데이터가 두번 읽혀짐
	close(acpt_sock);
	close(recv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
