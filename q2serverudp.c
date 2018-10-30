#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/time.h>
#define PORT 8080
void main()
{
int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
//int opt = 1;
//setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
//							sizeof(opt));
struct sockaddr_in address, cli_addr;
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);

bind(socket_fd, (struct sockaddr *)&address, sizeof(address));
//listen(socket_fd,3);
//int addrlen = sizeof(address);
//int new_socket = accept(socket_fd, (struct sockaddr *)&address, 
//				(socklen_t *)&addrlen);
char *hello = ".";
struct timeval start, end;
gettimeofday(&start,NULL);
int len;
char buffer[1024] = {0};
recvfrom(socket_fd, buffer, 1024, MSG_WAITALL, (struct sockaddr *)&cli_addr,&len);

sendto(socket_fd, hello, strlen(hello), MSG_CONFIRM, (struct sockaddr *)&cli_addr,
								len);

gettimeofday(&end,NULL);
double t1 = 0.0, t2 = 0.0;
t1 = start.tv_sec+(start.tv_usec/1000000.0);
t2 = end.tv_sec+(end.tv_usec/1000000.0);

printf("%s\n",buffer);
printf("RTT = %g", t2-t1);
}

