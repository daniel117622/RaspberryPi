#include "frame_write.hpp"
#define MAX 80
#define PORT 64000
#define SA struct sockaddr

int main()
{
	TcpSocket t1(PORT);
	t1.Connect(PORT);

	printf("Sending struct. \n");
	fConnect* sFrame = new fConnect();
	char * name = "MQTT";
	writefConnect(sFrame, name, 255);

	sendfConnect(*sFrame, &t1);

}
