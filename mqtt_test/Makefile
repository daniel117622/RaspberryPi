OBJS	= main.o client.o
SOURCE	= main.cpp client.cpp
HEADER	= frame_write.hpp
OUT	= server client
CC	 = g++
FLAGS	 = -g -c
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

client.o: client.cpp
	$(CC) $(FLAGS) client.cpp 


clean:
	rm -f $(OBJS) $(OUT)
