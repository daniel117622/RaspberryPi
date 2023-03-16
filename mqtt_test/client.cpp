#include "frame_write.hpp"

#define MAX 80
#define PORT 64001
#define SA struct sockaddr

int main()
{
	ClientSocket t1(PORT);
	t1.Connect();	
	printf("Sending struct. \n");
	fConnect sFrame = {.wLen = 0x0,.bType = 0x0, .bProtocol = 0x0, .cName = NULL, .bFlags = 0x0, .bKeepA = 0x0 };
	char * name = "MQTT";

	writefConnect(&sFrame, name, 255);
	printf("Protocol Level: 0x%hx\n", sFrame.bProtocol);


	sendfConnect(sFrame, &t1);
}
