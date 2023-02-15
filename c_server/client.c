#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#define MAX 80
#define PORT 63002
#define SA struct sockaddr

#include "frame.cpp"

void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) 
    {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        buff[n] = '\n';

        if (true)
        {   
            printf("You are sending a frame\n");
            sFrame s;
            sFrame *sp = &s;
            
            
            bzero(sp,sizeof(sFrame));
            sp->preamble = (char)0x69;
            sp->time[0] = (char)0x0;
            sp->type = (char)ACCELEROMETER;
            sp->v1[0] = (char)0xAA;  sp->v1[1] = (char)0xCA; sp->v1[2] = (char)0xCA; sp->v1[3] = (char)0xCA;
            sp->v2[0] = (char)0xFF;  sp->v2[1] = (char)0xCA; sp->v2[2] = (char)0xCA; sp->v2[3] = (char)0xCA;
            sp->v3[0] = (char)0xFF;  sp->v3[1] = (char)0xFF; sp->v3[2] = (char)0xCA; sp->v3[3] = (char)0xCA;

            printf("Generating checksum\n");

            send(sockfd,(char *) sp, sizeof(sFrame), 0);
            printf("Sent a test frame\n");
            continue;
        }
        
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}
 
int main( int argc, char** argv)
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
 
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
    printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
 
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(atoi(argv[1]));
 
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
        != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
 
    // function for chat
    func(sockfd);
 
    // close the socket
    close(sockfd);
}
