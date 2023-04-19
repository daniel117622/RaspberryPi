#include "frame_write.hpp"

#define MAX 80
#define PORT 64001
#define SA struct sockaddr

int main()
{
	uint16_t clientID = 0xCAFE;
	ClientSocket t1(PORT);
	t1.Connect();	
	printf("Sending struct. \n");
	fConnect sFrame;
	char name[] = "4115 0226 6338 5446 Cobrese :)";
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
	
	while(1)
	{
		t1.Receive();

		if ((uint8_t)*t1.buffer == 0xD0)
		{
			printf("Server pinged back...\n\n");
		}
		if ((uint8_t)*t1.buffer == 0x0A)
		{
			printf("Topic 1 Qos : %hx\n",*(t1.buffer + 4));
			printf("Topic 2 Qos : %hx\n",*(t1.buffer + 5));
			printf("Topic 3 Qos : %hx\n",*(t1.buffer + 6));
			break;
		}
		// What to send?
		while(1)
		{
			int op;
			printf("=== Select an action ===\n");
			printf("1) Ping\n");
			printf("2) Subscribe to default topics\n");
			printf("3) Publish to a topic\n");
			printf("--> ");
			scanf("%d", &op);
			if (op == 1)
			{
				*t1.buffer = 0xC0;
				*(t1.buffer + 1) = 0x00;	
				t1.Send(t1.buffer,2);			
				break;
			}
			if (op == 2)
			{
				char  names[3][64];
				char (* topics)[64] = names;
				
				for (int i = 0 ; i <= 2 ; i++) 
				{
					char temp[64];
					printf("\nTopic1: ");
					int n;
					scanf("%s%n",temp,&n);
					temp[n] = '\n';
					strncpy(names[i], temp, 64);
				}

				write_and_send_subscribe_packet(t1,topics,3,clientID);	// Send is included here
				break;
			}
			if (op == 3)
			{
				sendPublishFrame(t1,"ajedrez","libros en venta");
				break;
			}
			else
			{
				continue;
			}
		}

	}

	return 0;
}
