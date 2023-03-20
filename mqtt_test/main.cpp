#include "frame_write.hpp"
using namespace std;
#define PORT 64001
#define MAXCONN 256
#define DEBUG 1


int main() 
{    
    while(1)
    {
        printf("Server started.\n");
        TcpSocket t1(PORT);
        int x = 'H';
        t1.Listen();
        printf("Accepting...\n");
        t1.Accept();
            
        t1.Receive();
        printConnectFrame(t1);        
    }



    return 0;
}