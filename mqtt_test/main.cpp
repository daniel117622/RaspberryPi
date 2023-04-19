#include "frame_write.hpp"

using namespace std;
#define PORT 64001
#define MAXCONN 256
#define DEBUG 1

std::unordered_map<const char *, std::vector<uint16_t>> registers; 

void * timer_func(void * arg)
{
    return NULL;
}

void * worker(void * arg)




{
    TcpSocket t1 = *((TcpSocket*)arg);
    t1.Listen();
    t1.Accept();
    t1.Receive();
    printConnectFrame(t1);        
    // Validacion.
    uint16_t KA = ((fConnect*)t1.buffer)->bKeepA;
    uint8_t bType = *((uint8_t*)(t1.buffer + sizeof(uint16_t)));
    int timer = KA;

    pthread_t TID;

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
        else if ( (uint8_t) *t1.buffer == 0x82 ) // Subscribe packet
        {
            validate_and_send_suback(t1, &registers);
            printRequestedSubscribe(t1);
        }
        else
        {
            printf("Client disconnected\n");
            break;
        }
    }
}


int main() 
{   

    std::vector<uint16_t> v1; 
    std::vector<uint16_t> v2; 
    std::vector<uint16_t> v3; 

    registers["ajedrez"] = v1;
    registers["poker"] = v2;
    registers["blackjack"] = v3;


    while(1)
    {
        TcpSocket tc1 = TcpSocket(PORT);
        TcpSocket tc2 = TcpSocket(PORT);
        pthread_t TID[2];
        
        pthread_create(&TID[0], NULL,  worker, (void*)&tc1);
        pthread_create(&TID[1], NULL,  worker, (void*)&tc2);

        pthread_join(TID[0],NULL);
        pthread_join(TID[1],NULL);        
    }

    
    return 0;
}