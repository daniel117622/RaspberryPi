
Settings
Settings
Information
Makefile Generator
     
template:
Α.Delis (UOA), separate compilation, multiple project support (recommended)
standard:
undefined (system default)
​
Header and source files:
main.cpp frame_write.hpp
client.cpp frame_write.hpp
output file(s):
server client
clean command:
rm -f $(OBJS) $(OUT)
Output
     
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
© 2023 Nicomedes system by assistedcoding.eu
