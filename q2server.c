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
int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
int opt = 1;
setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
							sizeof(opt));
struct sockaddr_in address;
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);

bind(socket_fd, (struct sockaddr *)&address, sizeof(address));
listen(socket_fd,3);
int addrlen = sizeof(address);
int new_socket = accept(socket_fd, (struct sockaddr *)&address, 
				(socklen_t *)&addrlen);
char hello[1024] = {"."};
memset(hello,'d',1024);
struct timeval start, end;
gettimeofday(&start,NULL);
for(int i = 0; i<1024; i++)
{
	send(new_socket, hello, 1024, 0);
	char buffer[1024] = {0};
	read(new_socket, buffer, 1);
	printf("%s\n",buffer);
}
gettimeofday(&end,NULL);
double t1 = 0.0, t2 = 0.0;
t1 = start.tv_sec+(start.tv_usec/1000000.0);
t2 = end.tv_sec+(end.tv_usec/1000000.0);


printf("RTT = %g\n", t2-t1);
printf("throughput = %g\n",1024.0/(t2-t1));
}

