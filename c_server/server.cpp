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

#define MAX 80
#define PORT 64001

#include "tcp.h"

int main(int* argc, int** argv)
{
    std::cout<<"Hola mundo"<<std::endl;

    TcpSocket t1(64001);
    t1.Listen();
    t1.Accept();
    t1.Send("Hola\n",5);
    t1.Read();
   
    return 0;
}
