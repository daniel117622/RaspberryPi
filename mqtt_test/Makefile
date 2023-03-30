OBJS	= server.o
SOURCE	= server.cpp
HEADER	= 
OUT	= server
CC	 = g++
FLAGS	 = -g -c
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

server.o: server.cpp
	$(CC) $(FLAGS) server.cpp 


clean:
	rm -f $(OBJS) $(OUT)
