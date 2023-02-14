#define _XOPEN_SOURCE_EXTENDED 1
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <unordered_map>
#define MAX 80
#define PORT 64001

#include "tcp.cpp"
#include "frame.cpp"
// #include "json.h"

#include <list>
#include <iterator>

void * sum_to_n(void * parameter);
void * worker(void * parameter);

using namespace std;

int main(int* argc, int** argv)
{
    cout<<"Abriendo servidor"<<endl;



    TcpSocket t1(64001);
    TcpSocket t2(64002);
    TcpSocket t3(64003);
    TcpSocket t4(64004);

    t1.Listen();
    t2.Listen();
    t3.Listen();
    t4.Listen();

    pthread_t thread_id1;
    pthread_attr_t attr1;
    pthread_attr_init(&attr1); 
    pthread_create(&thread_id1,&attr1,worker,(void *)&t1);        
    

    pthread_t thread_id2;
    pthread_attr_t attr2;
    pthread_attr_init(&attr2);
    pthread_create(&thread_id2,&attr2,worker,(void *)&t2);        


    pthread_t thread_id3;
    pthread_attr_t attr3;
    pthread_attr_init(&attr3);
    pthread_create(&thread_id3,&attr3,worker,(void *)&t3);        


    pthread_t thread_id4;
    pthread_attr_t attr4;
    pthread_attr_init(&attr4);
    pthread_create(&thread_id4,&attr4,worker,(void *)&t4);   

    
    pthread_join(thread_id1,NULL);
    pthread_join(thread_id2,NULL);
    pthread_join(thread_id3,NULL);
    pthread_join(thread_id4,NULL);        

    return 0;
}

void * sum_to_n(void * parameter)
{
    int32_t acc = 0;
    int32_t n = *((int*)parameter);
    int32_t result = (n*(n+1))/2;
    
    int* p = (int*)parameter;
    *p = result;  

    pthread_exit(0);
}

void * worker (void * parameter)
{
    TcpSocket thisObject = *((TcpSocket*) parameter);

    thisObject.Accept();
    while (1)
    {
        thisObject.Read();
        thisObject.Send(thisObject.buffer,strlen(thisObject.buffer));
    }

    pthread_exit(0);
}






