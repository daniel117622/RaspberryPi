OBJS	= json_parsing_test.o tcp.o json.o 
SOURCE	= json_parsing_test.cpp tcp.cpp json.cpp 
HEADER	= 
OUT	= json_parse
CC	 = g++
FLAGS	 = -g -c -w -fcompare-debug-second
LFLAGS	 = -pthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)
	make clean

json_parsing_test.o: json_parsing_test.cpp
	$(CC) $(FLAGS) json_parsing_test.cpp -std=c++11

json.o: json.cpp
	$(CC) $(FLAGS) json.cpp -std=c++11

tcp.o: tcp.cpp
	$(CC) $(FLAGS) tcp.cpp -std=c++11

clean:
	rm -f $(OBJS) $(OUT)