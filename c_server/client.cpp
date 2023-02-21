#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#include <iostream>
#include <fstream>
#include <sstream>
#define MAX 80
#define PORT 63002
#define SA struct sockaddr


#include "frame.cpp"


void func(int sockfd)
{
    char buff[80];
    // JSON STUFF


    int n;
    for (;;) 
    {
        bzero(buff, 80);
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        buff[n] = '\n';

        char * token;
        char * cmdBuffer;

        rFrame r;
        rFrame* req = &r;

        enum state{
            INITIAL_COMMAND,
            FIRST_ARG,
            SECOND_ARG,
            INVALID_DATA,
        } STATE;
        STATE = INITIAL_COMMAND;
        // TOKENIZE FRAMES
        
        char * tmp = buff;
        printf("Parsing commmand...\n");
        std::istringstream iss(buff);
        while(iss.good())
        { 
            std::string tok;
            iss >> tok;
            const char * token = tok.c_str();

            switch (STATE)
            {
                case INITIAL_COMMAND:
                {
                    if (strcmp(token,"/accel") == 0)
                    {
                        req->sensor = (char)REQ_ACCEL;
                        STATE = FIRST_ARG;
                    }
                    else if (strcmp(token,"/magnet") == 0)
                    {
                        printf("You requested magnet\n");
                        req->sensor = (char)REQ_MAGNET;
                        STATE = FIRST_ARG;
                    }
                    else if (strcmp(token,"/gyro") == 0)
                    {
                        req->sensor = (char)REQ_GYRO;
                        STATE = FIRST_ARG;
                    }
                    else // YOU DIDNT TYPE A COMMAND
                    {
                        STATE = INVALID_DATA;
                    }
                    break;
                }
                case FIRST_ARG:
                {
                    if (strcmp(token,"x") == 0)
                    {
                        req->axis = (char)X_AXIS;
                        STATE = SECOND_ARG;
                    }
                    else if (strcmp(token,"y") == 0)
                    {
                        req->axis = (char)Y_AXIS;
                        STATE = SECOND_ARG;
                    }
                    else if (strcmp(token,"z") == 0)
                    {
                        req->axis = (char)Z_AXIS;
                        STATE = SECOND_ARG;
                    }
                    else if (strcmp(token,"xyz") == 0)
                    {
                        req->axis = (char)ALL_AXIS;
                        STATE = SECOND_ARG;
                    }
                    else // YOU DIDNT TYPE A COMMAND
                    {
                        STATE = INVALID_DATA;
                    }
                    break;
                }
                case INVALID_DATA:
                {
                    break;
                }
            }
            if (STATE == INVALID_DATA) { break ;}
        }

        // SEND STRCUTURE IN THE SOCKET
        req->preamble = (unsigned char)0xAA;
        printf("PREAMBLE: 0x%hhx\n",(unsigned char)req->preamble);
        
        req->datasize = sizeof(rFrame);
        //generateCheckSum(req);
        req->checksum = (unsigned char)0xFE;

        const char * buffer = (char *)req;
        
        printf("============== ALL FRAME ============\n");
        printf("PREAMBLE: 0x%hhx\n",(unsigned char) req->preamble);
        printf("SENSOR: 0x%hhx\n",(unsigned char) req->sensor);
        printf("DATA SIZE: 0x%hhx\n",(unsigned char) req->datasize);
        printf("AXIS: 0x%hhx\n",(unsigned char)req->axis);
        printf("CHECKSUM: 0x%hhx\n",(unsigned char)req->checksum);


        send(sockfd,(unsigned char*) req, sizeof(rFrame), NULL);
        
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
        // exit(0);
    }
    else
        printf("connected to the server..\n");
 
    // function for chat
    func(sockfd);
 
    // close the socket
    close(sockfd);
}
