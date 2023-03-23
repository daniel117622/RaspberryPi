#include "frame_write.hpp"

#define MAX 80
#define PORT 64001
#define SA struct sockaddr

int main()
{
	ClientSocket t1(PORT);
	t1.Connect();	
	printf("Sending struct. \n");
	fConnect sFrame;
	char name[] = "A long name";
	writefConnect(&sFrame, name, sizeof(name) , 255);
	sendfConnect(sFrame, t1);
	sleep(1); // Wait for server to reach send state.
	t1.Receive();
	printf("====================\n");
	printf("B1: 0x%hx\n", (uint8_t) *(t1.buffer + 0));
	printf("B2: 0x%hx\n", (uint8_t) *(t1.buffer + 1));
	printf("B3: 0x%hx\n", (uint8_t) *(t1.buffer + 2));
	printf("B4: 0x%hx\n", (uint8_t) *(t1.buffer + 3));
	printf("====================\n");

	sleep(1);
	*t1.buffer = 0xC0;
	*(t1.buffer + 1) = 0x00;
	t1.Send(t1.buffer, 2);
	sleep(1);
	t1.Receive();
	if ((uint8_t)*t1.buffer == 0xD0)
	{
		printf("Server pinged back...\n\n");
	}

}
