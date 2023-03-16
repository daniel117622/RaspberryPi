#define _XOPEN_SOURCE_EXTENDED 1
#define CLIENTSOCK_H
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
#define SOF 0xAA
#define BUFFSIZE 4096
class TcpSocket
{
public:
    int sockfd, newsockfd, portno,connect_sockfd;
    socklen_t clilen;

    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    int n;

    char buffer[BUFFSIZE];
    TcpSocket(int port)
    {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
        {
            std::cout << "Could not open socket" << std::endl;
        }
        bzero((char *)&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(port);

        if (int res = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))
        {
            std::cout << "Error en bind" << std::endl;
        }
        int optval = 1;
        setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));
    }
    void Listen()
    {
        listen(sockfd, 5);
    }
    void Accept()
    {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0)
        {
            std::cout << "Error con accept" << std::endl;
            return;
        }
        printf("Got connnection from %s port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
    }

    void Connect(int PORT)
    {
        newsockfd = connect(sockfd, (struct sockaddr*)&cli_addr, sizeof(cli_addr) );
        if (newsockfd < 0)
        {
            std::cout << "Error con connect" << std::endl;
            return;
        }
        printf("Connected to %s on port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
    }

    void Send(char *msg, int len)
    {
        send(sockfd, msg, len, 0);

    }

    void Receive()
    {
        bzero(buffer, 1024);
        recv(sockfd,buffer,BUFFSIZE,0);
    }

    ~TcpSocket()
    {
        close(newsockfd);
        close(sockfd);
    }
};
