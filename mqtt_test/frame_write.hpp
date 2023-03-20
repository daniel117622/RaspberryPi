#include <string.h>
#include <stdint.h>

#include "server.hpp"
#include "frame.hpp"
#include "client_handler.hpp"

void writefConnect(fConnect* frame , char * name, uint16_t keep_alive)
{
    char protocolLevel = 0x4;
    frame->bProtocol = 0x4;   
    uint16_t len = strlen(name);
    frame->wLen = len;
    frame->cName = name;
    frame->bFlags = 0x2;
    frame->bKeepA = keep_alive;
}

void sendfConnect(fConnect frame, ClientSocket* t1)
{
	
    
    uint8_t* protoFrame = (uint8_t*)malloc( sizeof(fConnect) - sizeof(char*) + frame.wLen );
    
    memcpy( (void*) protoFrame, (void*) &frame.wLen, sizeof(uint16_t) ); // Writes first two bytes
    // Obtain the string
    
    char * msgHolder = (char*)malloc( frame.wLen ); // Allocate the bytes specified in the length 
    char mqtt[4];
    memcpy( msgHolder, mqtt, frame.wLen );      
    memcpy( (void*) (protoFrame + sizeof(uint16_t)), msgHolder, frame.wLen );
    
    memcpy( (void*) (protoFrame + sizeof(uint16_t) + frame.wLen) , (void*) &frame.bProtocol, sizeof(uint8_t) );
    memcpy( (void*) (protoFrame + sizeof(uint16_t) + frame.wLen + sizeof(uint8_t)) , (void*) &frame.bFlags, sizeof(uint8_t) );
    memcpy( (void*) (protoFrame + sizeof(uint16_t) + frame.wLen + sizeof(uint8_t) + sizeof(uint8_t)) , (void*) &frame.bKeepA, sizeof(uint16_t) );

    t1->Send( (char*) protoFrame,  sizeof(fConnect) - sizeof(char*) + frame.wLen );
}

void printConnectFrame(TcpSocket t1) 
{
    printf("=============================\n");
    // When a TcpSocket object receives, it saves its contents on its internal buffer
    uint16_t len;
    memcpy( &len, (void*) t1.buffer, sizeof(uint16_t) );
    printf("Length: 0x%hX\n", len);

    char * msgHolder = (char*)malloc( len + 1 );
    memcpy( msgHolder, &t1.buffer[sizeof(uint16_t)], len + 1 );
    msgHolder[len] = '\0';
    printf("Name: %s\n", msgHolder);

    uint8_t protoLevel;
    memcpy( &protoLevel, t1.buffer + sizeof(uint16_t) + len, sizeof(uint8_t));
    printf("Protocol Level: 0x%hx\n", protoLevel);

    uint8_t cFlags;
    memcpy( &cFlags, t1.buffer + sizeof(uint16_t) + len + sizeof(uint8_t), sizeof(uint8_t));
    printf("Flags: 0x%hx\n", cFlags);

    uint16_t keepAlive;
    memcpy( &keepAlive, t1.buffer + sizeof(uint16_t) + len + 2*sizeof(uint8_t), sizeof(uint8_t));
    printf("Keep Alive: 0x%hx\n", keepAlive);
    printf("=============================\n");
}