#include <iostream>
#include <vector>
#include "server.hpp"
#include "frame.hpp"
using namespace std;
#define PORT 64000
static vector<TcpSocket*> conns;

void *accept_job(void *arg)
{
    size_t job = *(size_t*) arg;
    printf("Job %zu started\n");
    pthread_mutex_t mt = PTHREAD_MUTEX_INITIALIZER;
    
    
    TcpSocket t2 = TcpSocket(PORT);
    t2.Listen();
    t2.Accept();
    pthread_mutex_lock(&mt);
    conns.push_back(&t2);
    pthread_mutex_unlock(&mt);
}

void * handleConnection(void * arg)
{
    size_t job = *(size_t*) arg;
    printf("Job %zu started\n");
}

int main(int * argc, char** argv) 
{    
    TcpSocket t1 = TcpSocket(PORT);
    t1.Listen();
    t1.Accept();
    conns.push_back(&t1);

    while(1)
    {
        for (size_t it = 0 ; it <= conns.size() - 1; it ++)
        {
            if (conns.at( it )->newsockfd != -1 ) //After it has accepted.
            {
                auto curr = conns.at(it);
                // Launch a job that process the read and respond cycle

            }
            else if (conns.at( conns.size() - 1 )->newsockfd != -1) // If the last element of the vector is occupied then launch a job to accept
            {
                // Last server socket has been occupied
                // Launch a job that accepts a new connection
                pthread_t my_thread;
                int conn_number = conns.size() - 1;
                pthread_create(&my_thread, NULL, accept_job, &conn_number);
                pthread_join(my_thread, NULL);
            }
        }
    }


    return 0;
}