CC = gcc
RM = rm -f

default: all

all:thr

main:thr.c
	$(CC) thr.c -o thr
	./thr $(N)

clean veryclean:
	$(RM) thr
