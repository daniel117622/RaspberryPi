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
    free(protoFrame);   

}

void write_and_send_subscribe_packet(ClientSocket t1, char ** topics, uint8_t topics_len)
{
    // Size of packet identifier + protocol name + lenght + char bytes of each topic up to 3
    int total_size = 3; // fixed_header + packet_id

    for (int i = 0 ; i < topics_len ; i++)
    {
        total_size += (3 + strlen(*(topics + i))); // length + string + qos
    }

    uint8_t * protoFrame = (uint8_t*) malloc(total_size);
    ((fSubscribe*) protoFrame)->fixed_header = 0x82;
    ((fSubscribe*) protoFrame)->total_size = 0x02;
    ((fSubscribe*) protoFrame)->packet_id = 0x000A; 
    

    uint8_t * curr = protoFrame + 2* sizeof(uint16_t); // skip fixed header and skip packet_id
    // Write individual topics
    for (int i = 0 ; i < topics_len ; i++)
    {
        uint16_t this_topic_len = strlen(*(topics+i));
        memcpy(curr, &this_topic_len, 2);
        curr = curr + 2;
        memcpy(curr, *(topics+i) , 2);
        curr = curr + this_topic_len; // crashes in this line (sometimes)
        uint8_t QoS = 0x1;
        memcpy(curr, &QoS, 1);
        curr = curr + 1;
        ((fSubscribe*) protoFrame)->total_size += this_topic_len + 2 + 1; // length of this topic + length bytes + qos
    }


    t1.Send((char*) protoFrame, total_size);
    printf("Sent subscribe packet\n");
    free(protoFrame);

}

void validate_and_send_suback(TcpSocket t1)
{
    char * sendBuffer = (char*) malloc( 128 );

    uint8_t * curr = (uint8_t*)t1.buffer;
    curr = curr + 1;
    
    uint16_t this_topic_len = *((uint16_t*)curr);
    curr = curr + 2;
    
    memcpy(sendBuffer + 1, curr, this_topic_len);


    return;
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
    printf("Flags 0x%hx\n", bFlags);

    char * clientId = (char*) malloc( msgLen );
    memcpy(clientId, t1.buffer + sizeof(fConnect) - sizeof(char*) , msgLen );
    printf("Client ID: %s\n", clientId);
    printf("=============================\n");
    free(clientId);
}