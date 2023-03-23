#include "frame_write.hpp"
using namespace std;
#define PORT 64001
#define MAXCONN 256
#define DEBUG 1

int main() 
{    

    printf("Server started.\n");
    TcpSocket t1(PORT);
    t1.Listen();
    printf("Accepting...\n");
    t1.Accept();
    t1.Receive();
    printConnectFrame(t1);        
    // Validacion.
    uint16_t KA = *((uint16_t*)(t1.buffer + 2*sizeof(uint16_t) + *((uint16_t*)t1.buffer) + 2*sizeof(uint8_t)));
    uint8_t bType = *((uint8_t*)(t1.buffer + sizeof(uint16_t)));
    if (bType == 0x0) // If is a connect packet
    {
        fConnack frame;
        frame.bCode = 0x20;
        frame.wLen = 0x02;
        frame.bFlag = 0x0;
        frame.bType = 0x1;
        memcpy(t1.buffer, &frame, sizeof(fConnack));
        t1.Send(t1.buffer, sizeof(fConnack));
    }

    while(1)
    {
        t1.Receive();
        if ( (uint8_t)*t1.buffer == 0xC0 ) // PING REQUEST
        {
            *t1.buffer = 0xD0;
            *( t1.buffer + 1) = 0x00;
            t1.Send(t1.buffer, 2);
        }
        else
        {
            break;
        }
    }

    return 0;
}