// title : echo_selectserv.c
// date : 2024-06-14
// desc : 멀티 플렉싱 서버의 구현

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/select.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/time.h>

#define BUF_SIZE 30
void error_handling(char * message);

int main(int argc, char * argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	struct timeval timeout;
	fd_set reads, cpy_reads;

	socklen_t adr_sz;
	int str_len, i, fd_max, fd_num;
 	char buf[BUF_SIZE];
	if(argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");
	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	FD_ZERO(&reads);
	FD_SET(serv_sock, &reads);	// fd_set형 변수 reads에 서버 소켓을 등록 -> 데이터 수신여부를 관찰하는 관찰대상에 서버 소켓이 포함됨
	fd_max = serv_sock;			// -> 서버 소켓으로 수신된 데이터 존재 -> 연결요청이 존재했었음

	while(1)
	{
		cpy_reads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;

		if((fd_num = select(fd_max+1, &cpy_reads, 0, 0, &timeout)) == -1)	// select 함수의 네번째 세번째 인자가 비어있음 -> 목적에 맞게 필요한 인자만 전달 가능
			break;
		if(fd_num == 0)
			continue;

		// select함수가 1이상 반환했을 경우
		for(i=0;i<fd_max+1; i++)
		{
			if(FD_ISSET(i, &cpy_reads))	// 상태변화가 있었던 파일 디스크립터를 탐색
			{
				if(i == serv_sock)	// 상태 변화가 있었을 경우 서버 소켓에서 변화가 있었는지 확인
				{
					adr_sz = sizeof(clnt_adr);
					clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);	// 서버 소켓의 상태변화가 맞으면 연결 요청에 대한 수락
					FD_SET(clnt_sock, &reads);	// reads에 클라이언트와 연결된 소켓의 파일 디스크립터 정보를 등록
					if(fd_max < clnt_sock)
						fd_max = clnt_sock;
					printf("connected client : %d \n", clnt_sock);
				}
				else	// read message! 상태변화가 발생한 소켓이 서버 소켓이 아닌 경우 -> 수신할 데이터가 있는경우 -> 문자열인지 EOF인지 확인
				{
					str_len = read(i, buf, BUF_SIZE);
					if(str_len == 0)	// EOF인 경우 소켓을 종료, reads에서 해당 정보를 삭제
					{
						FD_CLR(i, &reads);
						close(i);
						printf("closed client : %d \n", i);
					}
					else	// 데이터가 문자열인 경우
					{
						write(i, buf, str_len);	// echo!
					}
				}
			}
		}

	}
	close(serv_sock);
	return 0;
}

void error_handling(char * buf)
{
	fputs(buf, stderr);
	fputc('\n', stderr);
	exit(1);
}
