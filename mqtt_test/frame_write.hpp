#include <string.h>
#include <stdint.h>

#include "server.hpp"
#include "frame.hpp"
#include "client_handler.hpp"

void writefConnect(fConnect* frame , char * clientName, uint16_t lenString , uint16_t keep_alive)
{
    frame->bType = 0x10;
    frame->wLen = lenString;
    frame->wProtNameLen = 0x04;
    frame->sProtoName[0] = 'M' ; frame->sProtoName[1] = 'Q' ; frame->sProtoName[2] = 'T' ; frame->sProtoName[3] = 'T' ; 
    frame->bVersion = 0x04;
    frame->bFlags = 0x02;
    frame->bKeepA = keep_alive;
    frame->wClientLen = lenString;
    frame->sClientID = clientName;
}

void sendfConnect(fConnect frame, ClientSocket t1)
{
	
    uint8_t* protoFrame = (uint8_t*)malloc( sizeof(fConnect) - sizeof(char*) + frame.wClientLen );
    memcpy(  (void*) (protoFrame), (void*) &frame, sizeof(fConnect) - sizeof(char*) );
    memcpy(  (void*) (protoFrame + sizeof(fConnect) - sizeof(char*)), frame.sClientID,  frame.wClientLen);
    t1.Send( (char*)protoFrame, sizeof(fConnect) - sizeof(char*) + frame.wClientLen  );    

}
void printConnectFrame(TcpSocket t1) 
{
    printf("=============================\n");
    // When a TcpSocket object receives, it saves its contents on its internal buffer
    uint8_t bFrameType = 0;
    memcpy( &bFrameType,    &((fConnect*)t1.buffer)->bType  , sizeof(uint8_t) );
    printf("Frame type: 0x%hx\n", bFrameType);

    uint16_t msgLen = 0;
    memcpy( &msgLen, &((fConnect*)t1.buffer)->wLen  , sizeof(uint16_t) );
    printf("Message length: 0x%hx\n", msgLen);

    uint16_t keepAlive = 0;
    memcpy( &keepAlive, &((fConnect*)t1.buffer)->bKeepA , sizeof(uint16_t) );
    printf("Keep Alive 0x%hx\n", keepAlive);

    uint8_t bVersion = 0;
    memcpy( &bVersion, &((fConnect*)t1.buffer)->bVersion , sizeof(uint16_t) );
    printf("Protocol version 0x%hx\n", bVersion);

    uint8_t bFlags = 0;
    memcpy( &bFlags, &((fConnect*)t1.buffer)->bFlags , sizeof(uint16_t) );
    printf("Flags 0x%hx\n", bVersion);

    char * clientId = (char*) malloc( ((fConnect*)t1.buffer)->wClientLen );
    memcpy(clientId, t1.buffer + sizeof(fConnect) - sizeof(char*) , msgLen );
    printf("Client ID: %s\n", clientId);
    printf("=============================\n");
}