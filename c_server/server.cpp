<<<<<<< HEAD
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

#include "tcp.h"
// #include "json.h"

#include <list>
#include <iterator>

void * sum_to_n(void * parameter);

using namespace std;

int main(int* argc, int** argv)
{
    cout<<"Abriendo servidor"<<endl;

    int int_data = 3;
    
    /* EJEMPLO DE UN EL USO DE PTHREAD
    pthread_t thread_id;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&thread_id,&attr,sum_to_n,&int_data);        

    pthread_join(thread_id,NULL);
    printf("%d",&int_data);    
    */

    TcpSocket t1(64001);
    t1.Listen();
    t1.Accept();
    while(1)
    {    

        t1.Read();
        t1.Send(t1.buffer,5);
    }
   
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






=======
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

#include "tcp.h"
// #include "json.h"

#include <list>
#include <iterator>

void * sum_to_n(void * parameter);

using namespace std;

int main(int* argc, int** argv)
{
    cout<<"Abriendo servidor"<<endl;

    int int_data = 3;
    
    /* EJEMPLO DE UN EL USO DE PTHREAD
    pthread_t thread_id;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&thread_id,&attr,sum_to_n,&int_data);        

    pthread_join(thread_id,NULL);
    printf("%d",&int_data);    
    */

    TcpSocket t1(64001);
    t1.Listen();
    t1.Accept();
    while(1)
    {    

        t1.Read();
        t1.Send(t1.buffer,5);
    }
   
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






>>>>>>> b2a8c6eaece50c14433b92981b946925d67dc2a9
