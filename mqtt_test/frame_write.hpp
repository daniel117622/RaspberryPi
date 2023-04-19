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

void write_and_send_subscribe_packet(ClientSocket t1, char  topics[3][64], uint8_t topics_len,uint16_t clientID)
{
    // Size of packet identifier + protocol name + lenght + char bytes of each topic up to 3
    int total_size = 2; // fixed_header + packet_id

    for (int i = 0 ; i < topics_len ; i++)
    {
        total_size += (3 + strlen(*(topics + i))); // length + string + qos
    }

    uint8_t * protoFrame = (uint8_t*) malloc(total_size);
    ((fSubscribe*) protoFrame)->fixed_header = 0x82;
    ((fSubscribe*) protoFrame)->total_size = 0x02;
    ((fSubscribe*) protoFrame)->packet_id = clientID;   
    

    uint8_t * curr = protoFrame + 2* sizeof(uint16_t); // skip fixed header and skip packet_id
    // Write individual topics
    for (int i = 0 ; i < topics_len ; i++)
    {
        uint16_t this_topic_len = strlen(*(topics+i));
        memcpy(curr, &this_topic_len, 2);
        curr = curr + 2;
        memcpy(curr, *(topics+i) , this_topic_len);
        curr = curr + this_topic_len; 
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
    char * recBuffer = (char* )malloc( sizeof(t1.buffer) );
    memcpy(recBuffer, t1.buffer, sizeof(t1.buffer));
    char * protoFrame = (char*) malloc(4 + 3); // Hardcoded as 3 topics
    uint16_t sourcePacketId = *((uint16_t*)(recBuffer + 2));
    // sourcePacketID should be copied to a global data structure


    char * curr = recBuffer + 4; // Position the ptr on first topic
    uint8_t numberOfTopics = 0; 
    for (int i = 0 ; i <= 2 ; i++)
    {
        curr += *((uint16_t*)curr)  + 2;
        uint8_t reqQos =  *curr;
        if (i <= 1) {curr++;} // Not go out of bounds
        *(protoFrame + 4 + i) = reqQos;
    }
    *protoFrame = 0x0A;
    *(protoFrame + 1) = 0x05;

    memcpy(protoFrame + 2, &sourcePacketId, 2);

    t1.Send(protoFrame, 3 + 4);

    free(protoFrame);
    free(recBuffer);
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

void printRequestedSubscribe(TcpSocket t1)
{
    uint8_t * curr = (uint8_t*)(t1.buffer + 4);

    for (int i = 0 ; i<= 2; i++)
    {
        uint16_t thisTopicLen = *((uint16_t*)curr);
        for (int j = 0 ; j <= thisTopicLen ; j++)
        {
            printf("%c", *(curr + 2 + j));
        }
        curr += 2 + thisTopicLen + 1;
        printf("\n");
    }
}