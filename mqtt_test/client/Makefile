OBJS	= client.o
SOURCE	= client.cpp
HEADER	= 
OUT	= client
CC	 = g++
FLAGS	 = -g -c
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

client.o: client.cpp
	$(CC) $(FLAGS) client.cpp 


clean:
	rm -f $(OBJS) $(OUT)
