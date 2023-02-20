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
#include "json.hpp"
using json = nlohmann::json;
#define SOF 0xAA

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

   void SendFrame(rFrame * prevReq, json* data) 
   {
	   std::string fStr;
	   float fVal;
      
      
      // GET THE DATA INTO SOME STRINGS
      if ((prevReq->sensor == REQ_GYRO) && (prevReq->axis == X_AXIS )) // SingleAxis - SingleData
      {
         SingleAxisSingleDataFrame sendFrame;
         sendFrame.preamble = SOF;
         sendFrame.sensor = REQ_GYRO;

         fStr = (*data)["gyroscope"][0]["timestamp"];
         fVal = (float)atof(fStr.c_str());
         memcpy(sendFrame.timestamp,(void*)&fVal,4*sizeof(char));

         fStr = (*data)["gyroscope"][0]["x"];
         fVal = (float)atof(fStr.c_str());
         memcpy(sendFrame.sData,(void*)&fVal,4*sizeof(char));
         

         
         generateCheckSum((void*)&sendFrame); // Writes the checksum byte
         send(newsockfd,(char * ) &sendFrame, sizeof(SingleAxisSingleDataFrame), NULL);
         return;
      }
/*
      else if ((prevReq->sensor == REQ_GYRO) && (prevReq->axis == Y_AXIS)) // SingleAxis - SingleData
      {
         SingleAxisSingleDataFrame sendFrame;
         sendFrame.preamble = SOF;
         sendFrame.sensor = REQ_GYRO;

         char * fStr = (*data)["gyroscope"][0]["timestamp"];
         float fVal = (float)atof(fStr);
         sendFrame.timestamp = fVal;

         char * fStr = (*data)["gyroscope"][0]["y"];
         float fVal = (float)atof(fStr);
         sendFrame.sData = fVal;
         

         generateCheckSum(sendFrame);
         send(newsockfd,(char * ) sendFrame, sizeof(SingleAxisSingleDataFrame), NULL);
         return;
      }
      else if ((prevReq->sensor == REQ_GYRO )&& (prevReq->axis == Z_AXIS)) // SingleAxis - SingleData
      {
         SingleAxisSingleDataFrame sendFrame;
         sendFrame.preamble = SOF;
         sendFrame.sensor = REQ_GYRO;

         char * fStr = (*data)["gyroscope"][0]["timestamp"];
         float fVal = (float)atof(fStr);
         sendFrame.timestamp = fVal;

         char * fStr = (*data)["gyroscope"][0]["z"];
         float fVal = (float)atof(fStr);
         sendFrame.sData = fVal;
         

         generateCheckSum(sendFrame);
         send(newsockfd,(char * ) sendFrame, sizeof(SingleAxisSingleDataFrame), NULL);
         return;
      }
*/
          

   }


   bool ReadCommand(rFrame* localFrame) // POINTER TO A FRAME THAT CONTAINS THE REQUEST FROM A CLIENT.
   {
      n = read(newsockfd,buffer,255);
      if (n < 0) {std::cout << "Error on read" << std::endl;}
      
      // CHECK IF RECEIVED BUFFER CONTAINS THE CORRECT PREAMBLE.
         
         // DISPLAY THE FRAME 
         printf("PREAMBLE: 0x%hhx\n",(unsigned char) buffer[0]);
         printf("TYPE: 0x%hhx\n",(unsigned char) buffer[1]);
         printf("TIMESTAMP: %f\n",(float) buffer[2]);
         printf("V1: %f\n",(float)buffer[6]);
         printf("V2: %f\n",(float)buffer[10]);
         printf("V3: %f\n",(float)buffer[14]);
         printf("CHECKSUM: 0x%hhx\n",(unsigned char)buffer[18]);
         
         /* SAVE THE FRAME IN LOCAL
         s->preamble = (unsigned char) buffer[0];
         s->type = (unsigned char) buffer[1];
         s->time = (float) buffer[2];
         s->v1 = (float) buffer[6];
         s->v2 = (float) buffer[10];
         s->v3 = (float) buffer[14];
         s->checkSum = (unsigned char)buffer[18];
         */
      return;
      
      memcpy(localFrame,buffer,sizeof(rFrame));
      std::cout << "Writing to local frame..." ;

   }

   ~TcpSocket()
   {
      close(newsockfd);
      close(sockfd);
   }

};

