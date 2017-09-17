#include "socket.h"

#define  IPSTR "182.254.244.212"
#define  PORT 80
#define  BUFSIZE 1024
#define  CLEAR(X) memset(X, 0, sizeof(X))

/* socket一些结构 */
struct sockaddr_in servaddr;
socklen_t len;
/* select要用的 */
fd_set t_set1;
struct timeval tv;

unsigned char *post[] = {"POST /xg/index.php/admin/upload/record HTTP/1.1\r\nHost: www.hicoder.cn\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: %d\r\n\r\n","key=%s&location=%s&device=%s"};

/*
 * socket初始化
 */
int socket_init(void)
{
	int sockfd = -1;
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("create socket failed!");
		return -1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(PORT);
	if(inet_pton(AF_INET, IPSTR, &servaddr.sin_addr) <= 0){
		printf("address translation failed!\n");
		return -1;
	}
	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
		printf("connect failed\n");
		return -1;
	}
	printf("connect to %s is OK\n", IPSTR);
	
	return sockfd;
}

/*
 * post表单填充：key、卡号、设备号
 */
void http_post_fill(char *buffer, const char *key_id, const char *location_id, const char *device_id)
{
	char http_post[256] = {0};
	char http_post_payload[128] = {0};

	CLEAR(http_post_payload);
	CLEAR(http_post);
	sprintf(http_post_payload, post[1], key_id, location_id, device_id);
	sprintf(http_post, post[0], strlen(http_post_payload));
	strcat(http_post, http_post_payload);
	strcpy(buffer, http_post);
}

/*
 * socket发送字符
 */
int socket_send(int sockfd, char *sbuff)
{
	int ret;

	if((ret = send(sockfd, sbuff, strlen(sbuff), 0)) < 0){
		printf("send failed!\n");
		return -1;
	}
	printf("send... \n%s\n...OK\nsend size: %d\n", sbuff, ret);
	return ret;
}

/*
 * 利用异步select进行socket接收处理
 */
int socket_recv(int sockfd, char *rbuff)
{
	int h, ret;
	while(1){
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		h = 0;
		h = select(sockfd + 1, &t_set1, NULL, NULL, &tv);
		if(h == 0)
			continue;
		if(h < 0){
			close(sockfd);
			printf("select error\n");
			return -1;
		}
		if(h > 0){
			CLEAR(rbuff);
			if((ret = recv(sockfd, rbuff, 4096, 0)) == 0){
				close(sockfd);
				printf("read %d ipmsg error!\n", ret);
				return -1;
			}
			printf("web return: %s\n", rbuff);
			break;
		}
	}
	return ret;
}

