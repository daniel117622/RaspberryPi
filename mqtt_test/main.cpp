#include "frame_write.hpp"

using namespace std;
#define PORT 64001
#define MAXCONN 256
#define DEBUG 1

std::unordered_map<const char *, std::string> registers; 
std::pair<pthread_t,int> timeAdmin[3];

void * launchTimeManagment( void * arg )
{
    std::pair<pthread_t, int>* timeAdmin = (std::pair<pthread_t, int>*)arg;
    while(1)
    {
        for ( int i = 0 ; i <= 1 ; i++ )
        {
            if ( timeAdmin[i].second != -1 ) // Time is different from "null"
            {
                timeAdmin[i].second += -1; //substract one second
            }
        }
        for ( int i = 0 ; i <=  1 ; i++)
        {
            if ( timeAdmin[i].second == 0 )
            {
                // Nothing happens but the parent thread (worker) kills itself
            }
        }
        sleep(1);
        }

}

void * worker(void * arg)

{
    std::pair<TcpSocket*, uint32_t>* arg_tmp = (std::pair<TcpSocket*, uint32_t>*)arg;

    TcpSocket t1 = *(arg_tmp->first);
    uint32_t myTimeSlot = arg_tmp->second;
    t1.Listen();
    t1.Accept();
    t1.Receive();
    printConnectFrame(t1);        
    // Validacion.
    uint16_t KA = ((fConnect*)t1.buffer)->bKeepA;
    timeAdmin[myTimeSlot].second = KA;

    pthread_t TID;
    pthread_create(&TID, NULL,  launchTimeManagment, (void*)timeAdmin);

    uint8_t bType = *((uint8_t*)(t1.buffer + sizeof(uint16_t)));
    //int timer = KA; //CAMBIO
    
    //pthread_t TID; //CAMBIO

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

        if (timeAdmin[myTimeSlot].second <= 0) 
        {
            close(t1.sockfd);
            printf("Idle client. Disconnected.\n");
            return 0;
        }

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
        else if ( (uint8_t) *t1.buffer == 0x30 ) // Publish packet
        {
            validate_and_send_puback(t1,&registers);
        }
        else
        {
            printf("Client disconnected\n");
            break;
        } 
    }
    return 0;
}



int main() 
{   

    registers["ajedrez"] = std::string("");
    registers["poker"] = std::string("");
    registers["blackjack"] = std::string("");


    while(1)
    {
        TcpSocket tc1 = TcpSocket(PORT);
        std::pair<TcpSocket*, uint32_t> conninfo1 = { &tc1, 0 };
        TcpSocket tc2 = TcpSocket(PORT);
        std::pair<TcpSocket*, uint32_t> conninfo2 = { &tc2, 1 };
        pthread_t TID[2];
        
        timeAdmin[0].first = TID[0];
        timeAdmin[0].second = -1; 
        pthread_create(&TID[0], NULL,  worker, (void*)&conninfo1);
        timeAdmin[1].first = TID[1];
        timeAdmin[1].second = -1; 
        pthread_create(&TID[1], NULL,  worker, (void*)&conninfo2);

        

        pthread_join(TID[0],NULL);
        pthread_join(TID[1],NULL);        
    }

    
    return 0;
}