#include "frame.hpp"
#include <string.h>
#include <stdint.h>
#include "server.hpp"
void * writefConnect(fConnect* frame ,char * name, unsigned int keep_alive)
{
    char protocolLevel = 0x4;
    memcpy( (void*) frame->bProtocol, (void*) &protocolLevel, sizeof(char) );
    uint16_t len = strlen(name);
    memcpy( (void*) frame->wLen, (void*) &len , 2 * sizeof(uint16_t) );
    memcpy( (void*) frame->cName, name, sizeof(char* )); // Only the pointer is copied
    char connFlags = 0x2;
    memcpy( (void*) frame->bFlags, (void*) &connFlags, sizeof(char) );
    uint16_t keep = keep_alive;
    memcpy( (void*) frame->bKeepA, (void*) &keep, sizeof(uint16_t) );
}

void sendfConnect(fConnect frame, TcpSocket* t1)
{
    uint8_t* protoFrame = (uint8_t*)malloc( sizeof(fConnect) - sizeof(char*) + frame.wLen );

    memcpy( (void*) protoFrame, (void*) frame.wLen, sizeof(uint16_t) ); // Writes first two bytes
    // Obtain the string
    char * msgHolder = (char*)malloc( frame.wLen ); // Allocate the bytes specified in the length
    memcpy( msgHolder, frame.cName, frame.wLen );
    memcpy( (void*) (protoFrame + sizeof(uint16_t)), msgHolder, frame.wLen );
    
    memcpy( (void*) (protoFrame + sizeof(uint16_t) + frame.wLen) , (void*) frame.bProtocol, sizeof(uint8_t) );
    memcpy( (void*) (protoFrame + sizeof(uint16_t) + frame.wLen + sizeof(uint8_t)) , (void*) frame.bFlags, sizeof(uint8_t) );
    memcpy( (void*) (protoFrame + sizeof(uint16_t) + frame.wLen + sizeof(uint8_t) + sizeof(uint8_t)) , (void*) frame.bKeepA, sizeof(uint16_t) );

    t1->Send( (char*) protoFrame,  sizeof(fConnect) - sizeof(char*) + frame.wLen );
}

void printConnectFrame(TcpSocket t1) 
{
    // When a TcpSocket object receives, it saves its contents on its internal buffer
    uint16_t len;
    memcpy( &len, (void*) t1.buffer, sizeof(uint16_t) );
    printf("Length: 0x%hX", len);

    char * msgHolder = (char*)malloc( len + 1 );
    memcpy( msgHolder, &t1.buffer[sizeof(uint16_t)], len + 1 );
    msgHolder[len] = '\0';
    printf("Name: %s", msgHolder);

    uint8_t protoLevel;
    memcpy( &protoLevel, t1.buffer + sizeof(uint16_t) + len, sizeof(uint8_t));
    printf("Protocol Level: 0x%hx", protoLevel);

    uint8_t cFlags;
    memcpy( &cFlags, t1.buffer + sizeof(uint16_t) + len + sizeof(uint8_t), sizeof(uint8_t));
    printf("Flags: 0x%hx", cFlags);

    uint16_t keepAlive;
    memcpy( &keepAlive, t1.buffer + sizeof(uint16_t) + len + 2*sizeof(uint8_t), sizeof(uint8_t));
    printf("Keep Alive: 0x%hx", keepAlive);
}