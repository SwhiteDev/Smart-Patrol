#ifndef   SOCKET_H
#define  SOCKET_H

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


int socket_init(void);

void http_post_fill(char *buffer, const char *key_id, const char *location_id, const char *device_id);

int socket_send(int sockfd, char *sbuff);

int socket_recv(int sockfd, char *rbuff);
#endif


