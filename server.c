#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#define PORT 8080
#define BUF_SIZE 256
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    // Sockets are highly configurable beasts, setting options here
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    //struct sockaddr_in address members initialization
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    // listen now, queued max 3
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    // when a connection arrives, assign it to a new socket
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    char buffer[256];
    valread = read( new_socket, buffer, 256);
    // parse the buffer, break into request type(GET/HEAD) and file requested
    int i = 0;
    char *p = strtok (buffer, " "); //tokenize on space
    char *array[3];
    while (p != NULL)
    {
        array[i++] = p;
        p = strtok (NULL, " ");
    }
    if((strcmp(array[0],"GET")==0))
    {
        //get implementation
        ///////////////////// file handling ///////////////////////////
        // Open the file that we wish to transfer
        char filename[100];
        char tempfilename[100];
        strcpy(tempfilename,array[1]);
        strcpy(filename,&tempfilename[1]);
            FILE *fp = fopen(filename,"rb");
            if(fp==NULL)
            {
                //printf("File open error");
                char err_msg[100];
                strcpy(err_msg,"File open error");
                printf("%ld",strlen(err_msg));
                write(new_socket, err_msg, 100);
                return 1;
            }
            // fetching file properties from my system with stat() function and structure // this is Linux only (perhaps)
            struct stat fileinfo;
            stat(filename, &fileinfo);
            int file_size = fileinfo.st_size;
            char tempbuff[BUF_SIZE];
            char file_modified_time[50];
            strftime(file_modified_time, sizeof(file_modified_time), "%Y-%m-%d %H:%M:%S", localtime(&fileinfo.st_mtime));
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            char date_of_request[64];
            strftime(date_of_request, sizeof(date_of_request), "%Y-%m-%d %H:%M:%S", tm);
            sprintf(tempbuff,"HTTP/1.0 200 OK\r\nDate:%s\r\nContent-Type:%s\r\nContent-Length:%d\r\nLast-Modilfied:%s\r\n\r\n",date_of_request,"text-file",file_size,file_modified_time);
            // Read data from file and send it
            //write(new_socket, tempbuff, strlen(tempbuff));
            // there are some memory leak problems with write()
            // send() seems to work better here
            send(new_socket,tempbuff,strlen(tempbuff),0);
        for (;;)
        {
            // First read file in chunks of BUF_SIZE bytes
            unsigned char buff[BUF_SIZE]={0};
            int nread = fread(buff,1,BUF_SIZE,fp);
            printf("Bytes read %d \n", nread);
            // If read was success, send data.
            if(nread > 0)
            {
                printf("Sending \n");
                write(new_socket, buff, nread);
            }
            //  There is something tricky going on with read ..
            //  Either there was error, or we reached end of file.
            if (nread < BUF_SIZE)
            {
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }

        }
        ///////////////////////////////////////////////////////////////
    }

    else if(strcmp(array[0],"HEAD")==0)
    {
    //head implementaion (same as get , just don't send the requested file)
    ///////////////////// file handling ///////////////////////////
    // Open the file that we wish to transfer
    char filename[100];
    char tempfilename[100];
    strcpy(tempfilename,array[1]);
    strcpy(filename,&tempfilename[1]);
        FILE *fp = fopen(filename,"rb");
        if(fp==NULL)
        {
            char err_msg[100];
            strcpy(err_msg,"File open error");
            printf("%ld",strlen(err_msg));
            write(new_socket, err_msg, 100);
            return 1;
        }
        // fetching file properties from my system with stat() function and structure // this is Linux only (perhaps)
        struct stat fileinfo;
        stat(filename, &fileinfo);
        int file_size = fileinfo.st_size;
        char buff[BUF_SIZE];
        char file_modified_time[50];
        strftime(file_modified_time, sizeof(file_modified_time), "%Y-%m-%d %H:%M:%S", localtime(&fileinfo.st_mtime));
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char date_of_request[64];
        strftime(date_of_request, sizeof(date_of_request), "%Y-%m-%d %H:%M:%S", tm);
        sprintf(buff,"HTTP/1.0 200 OK\r\nDate:%s\r\nContent-Type:%s\r\nContent-Length:%d\r\nLast-Modilfied:%s\r\n",date_of_request,"text-file",file_size,file_modified_time);
        // Read data from file and send it
        //write(new_socket, buff, sizeof(buff));
        send(new_socket,buff,strlen(buff),0); // last parameter is a flag that should be = 0
    }
    else
    {
        //Incorrect header request or header request not implemented on server side
        char err_msg[100];
        strcpy(err_msg,"Incorrect header request or header request not implemented on server side");
        write(new_socket, err_msg, strlen(err_msg));
    }
    return 0;
}
