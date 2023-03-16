#include "frame_write.hpp"
using namespace std;
#define PORT 64000
#define MAXCONN 256
#define DEBUG 1


int main() 
{    
    int x = 5;
    int y = x + 3;
    printf("Server started.");
    TcpSocket t1(PORT);
    t1.Listen();
    t1.Accept();
        
    t1.Receive();
    printConnectFrame(t1);        


    return 0;
}