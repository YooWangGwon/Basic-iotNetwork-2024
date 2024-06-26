// title : sep_serv2.c
// date : 2024-06-17
// desc : 파일 디스크립터 복사 후 스트림의 분리

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	char buf[BUF_SIZE]={0,};
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;

	FILE * readfp;
	FILE * writefp;

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

	listen(serv_sock, 5);

	clnt_adr_sz = sizeof(clnt_adr);

	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

	readfp = fdopen(clnt_sock, "r");
	writefp = fdopen(dup(clnt_sock), "w");

	fputs("FROM SERVER : Hi~ Client? \n", writefp);
	fputs("I love all of the world \n", writefp);
	fputs("You are awesome! \n", writefp);
	fflush(writefp);

	shutdown(fileno(writefp), SHUT_WR);
	fclose(writefp);

	fgets(buf, sizeof(buf), readfp); fputs(buf, stdout);
	fclose(readfp);
	return 0;
}
