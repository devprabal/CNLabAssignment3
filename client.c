// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080
#define BUF_SIZE 256

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    // create a socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    //set the entire memory occupied by serv_addr object of sockaddr_in to 0 for just a safeguard
    memset(&serv_addr, '0', sizeof(serv_addr));
    // initialize the fields of object serv_addr of struct sockaddr_in
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    // Convert IPv4 and IPv6 addresses from text to binary form and save it in the corresponding field of serv_addr
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    // serv_addr is of struct sockaddr_in which must be type casted to struct sockaddr
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    else
    {
    	printf("\nConnection Established. Type HTTP message...\n");
    }
    char http_request_msg[256];
    scanf ("%[^\n]%*c", http_request_msg);
    send(sock , http_request_msg , strlen(http_request_msg) , 0 );
    printf("HTTP message sent. Waiting for reply...\n");
    ///////////////// file handling /////////////////////////
    /* Create file where data will be stored */
    char filename[100];
    strcpy(filename, "rcvdfile.txt");
    FILE *fp = fopen(filename, "ab");
    if(fp == NULL)
    {
        printf("Error opening file");
        return 1;
    }
    /* Receive data in chunks of BUF_SIZE bytes */
    int bytesReceived = 0;
    char buff[BUF_SIZE];
    memset(buff, '0', sizeof(buff));
    while((bytesReceived = read(sock, buff, BUF_SIZE)) > 0)
    {
        printf("Bytes received %d\n",bytesReceived);
        fwrite(buff, 1,bytesReceived,fp);
    }

    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }
    //////////////////////////////////////////////////////
    return 0;
}
