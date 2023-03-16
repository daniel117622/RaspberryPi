#include "frame_write.hpp"
using namespace std;
#define PORT 64000
#define MAXCONN 256
#define DEBUG 1


int main() 
{    

    printf("Server started.\n");
    TcpSocket t1(PORT);
    t1.Listen();
    t1.Accept();
        
    t1.Receive();
    printConnectFrame(t1);        


    return 0;
}