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
#include "json.h"

#include <list>
#include <iterator>

using namespace std;
int main(int* argc, int** argv)
{
    cout<<"Hola mundo"<<endl;

    list<GenericData> c1,c2,c3;
    unordered_map< string , list<GenericData>* > map;

    map.insert({string("gyroscope"),     &c1});
    map.insert({string("accelerometer"), &c2});
    map.insert({string("magnetometer"),  &c3});

   
    return 0;
}
