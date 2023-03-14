#include <iostream>
#include <vector>
#include <signal.h>
#include "server.hpp"
#include "frame.hpp"
using namespace std;
#define PORT 64000
static vector<TcpSocket*> conns;

#define DEBUG 1

void *accept_job(void *arg)
{
    size_t job = *(size_t*) arg;
    printf("Accept job %zu started\n");
    pthread_mutex_t mt = PTHREAD_MUTEX_INITIALIZER;
    
    TcpSocket t2 = TcpSocket(PORT);

    pthread_mutex_lock(&mt);
    conns.push_back(&t2);
    pthread_mutex_unlock(&mt);    

    t2.Listen();
    t2.Accept();

}

void * handleConnection(void * arg)
{
    printf("Job handleConnection started\n");
    TcpSocket* tsock = (TcpSocket*) arg;
    tsock->Receive();
    conns.push_back(tsock);
    printf("%s",tsock->buffer);    
}

int main(int * argc, char** argv) 
{    
    TcpSocket t1 = TcpSocket(PORT);
    t1.Listen();
#ifdef DEBUG
        printf("Before accept\n");
#endif 
    t1.Accept();
    conns.push_back(&t1);

    vector<pthread_t> threads;
    vector<int> ret;
    while(1)
    {
        // pthread_t *threads = (pthread_t*)malloc( (conns.size() - 1) * sizeof(pthread_t) );
        // int *ret = (int*)malloc( (conns.size() - 1) * sizeof(int) );
                
        for (size_t it = 0 ; it <= conns.size() - 1; it ++)
        {
            if (conns.size() == 0) // No connections? Accept a new one
            {
                pthread_t tid;
                threads.push_back(tid); 
                pthread_create(&threads[it], NULL, accept_job, NULL);
                continue;
            }      
            else if (conns.at( it )->newsockfd != -1 ) //After it has accepted.
            {   
                ret[it] = pthread_kill(threads[it],0);
                
                auto curr = conns.at(it);
                // Launch a job that process the read and respond cycle. 
                int conn_number = it;
                pthread_create(&threads[it], NULL, handleConnection, (void*) curr);
                                

                if (ret[it] != 0) //If it is 0, that means the thread is still running
                {
                    conns.erase(conns.begin() + it);
                    printf("Thread %d has finished\n", it);
                }
            }

            else if(conns.at( conns.size() - 1 )->newsockfd != -1) // If the last element of the vector is occupied then launch a job to accept
            {
                // Last server socket has been occupied
                // Launch a job that accepts a new connection
                #ifdef DEBUG
                        printf("\nInstantiated new socket\n");
                #endif
                int conn_number = conns.size() - 1;
                pthread_create(&threads[it], NULL, accept_job, &conn_number);
            }
        }
        sleep(5);
#ifdef DEBUG
        printf("\nEnd while\n");
#endif
    }
    


    return 0;
}