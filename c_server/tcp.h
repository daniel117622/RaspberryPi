#define _XOPEN_SOURCE_EXTENDED 1
#define CLIENTSOCK_H
#include <iostream>
//#define _BSD_SOURCE
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

class TcpSocket
{
   private:
   int sockfd,newsockfd,portno;
   socklen_t clilen;

   char buffer[1024];
   struct sockaddr_in serv_addr;
   struct sockaddr_in cli_addr;
   int n;
   public:
   TcpSocket(int port)
   {
         sockfd = socket(AF_INET,SOCK_STREAM,0);
         if (sockfd < 0 ) {std::cout << "Could not open socket" << std::endl;}
         bzero((char *) &serv_addr,sizeof(serv_addr));
         serv_addr.sin_family = AF_INET;
         serv_addr.sin_addr.s_addr = INADDR_ANY;
         serv_addr.sin_port = htons(port);   
         
         if ( bind(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr) ) ) {std::cout << "Error con bind" << std::endl;} 

      }
   void Listen() 
   {
      std::cout<<"Listening..."<<std::endl;
      listen(sockfd,5);
   }  
   void Accept()
   {
      newsockfd = accept(sockfd,(struct sockaddr*) &cli_addr,&clilen);
      if (newsockfd < 0) { std::cout << "Error con accept"  << std::endl; }
      printf("Got connnection from %s port %d\n", inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port));
   }
   void Send(char * msg,int len)
   {
      send(newsockfd,msg,len,0);
      bzero(buffer,1024);
   }
   void Read()
   {
      n = read(newsockfd,buffer,255);
      if (n < 0) {std::cout << "Error on read" << std::endl;}
      std::cout << buffer << std::endl;
   }

   ~TcpSocket()
   {
      close(newsockfd);
      close(sockfd);
   }

};

