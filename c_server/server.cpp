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


#include "tcp.cpp"
// #include "json.h"

#include <list>
#include <iterator>
#include <signal.h>

void * sum_to_n(void * parameter);
void * worker(void * parameter);
void sig_handler(int signum);

using namespace std;

sFrame frameBuffer;

int main(int* argc, char** argv)
{
    cout<<"Abriendo servidor"<<endl;

    int n = atoi(argv[1]);

    TcpSocket t1(n);
    TcpSocket t2(n+1);
    TcpSocket t3(n+2);
    TcpSocket t4(n+3);

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



void * worker (void * parameter)
{
    TcpSocket thisObject = *((TcpSocket*) parameter);
    thisObject.Accept();
    while (1)
    {
        thisObject.ReceiveFrame(&frameBuffer);
        thisObject.Send(thisObject.buffer,strlen(thisObject.buffer));
    }

    pthread_exit(0);
}




