#include <iostream>
// #define _BSD_SOURCE
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#define BUFFERSIZE 1024
class ClientSocket
{
    public:
    int sockfd;
    int status;
    struct sockaddr_in serv_addr;
    char buffer[BUFFERSIZE];

    ClientSocket(int PORT) 
    { 
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\nSocket not created.\n");
        }
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
        if ( inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0 )
        {
            printf("\nInvalid address.\n");
        }                        
    }
    void Connect()
    {
        
        if ((status = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr) )) < 0)
        {
            printf("\nConnect failed.\n");
        }     
        printf("Connecting to server. \n");  
    }
    void Send(char * msg, size_t len)
    {
        send(sockfd, msg, len, 0);
    }

};