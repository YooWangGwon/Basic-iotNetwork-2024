// title : set_buf.c
// date : 2024-06-13
// desc : 버퍼의 크기 조절

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;
	int snd_buf = 1024*3, rcv_buf=1024*3;
	int state;
	socklen_t len;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, sizeof(rcv_buf));	// 입력 버퍼 크기를 3KByte로 변경
	if(state)
		error_handling("setsockopt() error!");

	state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, sizeof(snd_buf));	// 출력 버퍼 크기를 3KByte로 변경
	if(state)
		error_handling("setsockopt() error!");

	len = sizeof(snd_buf);
	state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, &len);
	if(state)
		error_handling("getsockopt() error!");


	len = sizeof(rcv_buf);
	state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, &len);
	if(state)
		error_handling("getsockopt() error!");


	printf("Input buffer size: %d \n", rcv_buf);
	printf("Output buffer size: %d \n", snd_buf);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
