#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 8080
void main()
{
int socket_fd;
socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
struct sockaddr_in address;
address.sin_family = AF_INET;
address.sin_port = htons(PORT);
//inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
address.sin_addr.s_addr = INADDR_ANY;
//connect(socket_fd, (struct sockaddr *)&address, sizeof(address));

char buffer[1] = {0};
char *hello = ".";
sendto(socket_fd, hello, strlen(hello),MSG_CONFIRM, (struct sockaddr *)&address,
				sizeof(address));
int len;
recvfrom(socket_fd, buffer, 1024, MSG_WAITALL, (struct sockaddr *)&address, &len);
printf("%s\n",buffer);
close(socket_fd);
}

