#include "frame_write.hpp"

#define MAX 80
#define PORT 64000
#define SA struct sockaddr

int main()
{
	ClientSocket t1(PORT);
	printf("Connecting to server. \n");
	// t1.Connect();	
	printf("Sending struct. \n");
	fConnect* sFrame = new fConnect();
	const char * name = "MQTT";
	writefConnect(sFrame, name, 255);
	printf("WriteConnect finished. \n");
	printf("DEBUG\n"); 	
	sendfConnect(*sFrame, &t1);
}
