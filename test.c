#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/types.h>

#define IPSTR "192.168.123.242"
#define PORT 8080
#define BUFSIZE 1024
#define CLEAR(X) memset(X, 0, sizeof(X))

unsigned char *post = "POST /Xungeng/patrol/stageUpdate HTTP/1.1\r\nHost: jiangh.ngrok.cc\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: %d\r\n\r\nkey=iot&location=%s&device=%s";

int main(int argc, char **argv)
{
	int sockfd;
	int ret, i, h;
	struct sockaddr_in servaddr;
	char post_buf[BUFSIZE];
	char buf[BUFSIZE];
	char *str;
	socklen_t len;
	fd_set t_set1;
	struct timeval tv;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("create socket failed!");
		exit(0);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(PORT);
	if(inet_pton(AF_INET, IPSTR, &servaddr.sin_addr) <= 0){
		printf("address translation failed!\n");
		exit(0);
	}
	
	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
		printf("connect failed\n");
		exit(0);
	}

	printf("connect to %s is OK\n", IPSTR);

	CLEAR(post_buf);
	sprintf(post_buf, post, 42, argv[1], argv[2]);

	if((ret = send(sockfd, post_buf, strlen(post_buf), 0)) < 0){
		printf("send failed!\n");
		exit(0);
	}
	printf("send... \n%s\n...OK\nsend size: %d\n", post_buf, ret);

//	FD_ZERO(&t_set1);
//	FD_SET(sockfd, &t_set1);

//	while(1){
		sleep(2);
//		tv.tv_sec = 0;
//		tv.tv_usec = 0;
//		h = 0;
//		h = select(sockfd + 1, &t_set1, NULL, NULL, &tv);
//		if(h == 0)
//			continue;
//		if(h < 0){
//			close(sockfd);
//			printf("select error\n");
//			return -1;
//		}
//		if(h > 0){
			CLEAR(buf);
			if(0 == recv(sockfd, buf, 4096, 0)){
				close(sockfd);
				printf("read ipmsg error!\n");
				return -1;
			}
			printf("web return: %s\n", buf);
	//	}

	//}


}

