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
socket_fd = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in address;
address.sin_family = AF_INET;
address.sin_port = htons(PORT);
inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
connect(socket_fd, (struct sockaddr *)&address, sizeof(address));
char buffer[1024] = {0};
char *hello = ".";
while(read(socket_fd, buffer, 1024) >0)
{
printf("%s\n",buffer);
send(socket_fd, hello, strlen(hello), 0);
}
}

