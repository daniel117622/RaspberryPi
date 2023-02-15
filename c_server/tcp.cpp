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
#include <pthread.h>

#include "frame.cpp"

class TcpSocket
{
   public:
   int sockfd,newsockfd,portno;
   socklen_t clilen;

   struct sockaddr_in serv_addr;
   struct sockaddr_in cli_addr;
   int n;

   char buffer[1024];
   TcpSocket(int port)
   {
         sockfd = socket(AF_INET,SOCK_STREAM,0);
         if (sockfd < 0 ) {std::cout << "Could not open socket" << std::endl;}
         bzero((char *) &serv_addr,sizeof(serv_addr));
         serv_addr.sin_family = AF_INET;
         serv_addr.sin_addr.s_addr = INADDR_ANY;
         serv_addr.sin_port = htons(port);   
         
         if ( int res = bind(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr) ) ) {std::cout << strerror(res) << std::endl;} 

      }
   void Listen() 
   {
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
      msg[len] = '\n'; 
      send(newsockfd,msg,len,0);
      bzero(buffer,1024);
   }

   void SendFrame(sFrame * s)
   {
      uint8_t msgLength = sizeof(sFrame);
      writePreamble(s);
      generateCheckSum(s); // Writes the checksum byte
      send( newsockfd , (char *) s , msgLength , 0 );
   }

   void ReceiveFrame(sFrame * s) // Reference to write on it
   {
      uint8_t msgLength = sizeof(sFrame);
      n = read(newsockfd,s,msgLength);
      if (n < 0) {std::cout << "Error on read" << std::endl;}
      if (validateCheckSum(s)) { std::cout << "Corrupted checksum" << std::endl; }
      std::cout << (char)s->preamble << std::endl;
   }

   void Read(sFrame *s)
   {
      n = read(newsockfd,buffer,255);
      if (n < 0) {std::cout << "Error on read" << std::endl;}
      // CHECK IF RECEIVED BUFFER CONTAINS THE CORRECT PREAMBLE.
      if (*buffer == (char)0x0F) // PREABMLE
      {
         
         // DISPLAY THE FRAME 
         printf("PREAMBLE: 0x%hhx\n",(unsigned char) buffer[0]);
         printf("TYPE: 0x%hhx\n",(unsigned char) buffer[1]);
         printf("TIMESTAMP: %f\n",(float) buffer[2]);
         printf("V1: %f\n",(float)buffer[6]);
         printf("V2: %f\n",(float)buffer[10]);
         printf("V3: %f\n",(float)buffer[14]);
         printf("CHECKSUM: 0x%hhx\n",(unsigned char)buffer[18]);
         // SAVE THE FRAME IN LOCAL
         s->preamble = (unsigned char) buffer[0];
         s->type = (unsigned char) buffer[1];
         s->time = (float) buffer[2];
         s->v1 = (float) buffer[6];
         s->v2 = (float) buffer[10];
         s->v3 = (float) buffer[14];
         s->checkSum = (unsigned char)buffer[18];
         return;
      }

      std::cout << "No frame received" ;
   }

   ~TcpSocket()
   {
      close(newsockfd);
      close(sockfd);
   }

};

