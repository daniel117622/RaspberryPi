CC = g++
CFLAGS = -Wall -std=c++11

SRCDIR = .
OBJDIR = obj
BINDIR = bin

MAIN = $(BINDIR)/main
CLIENT = $(BINDIR)/client

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

all: $(MAIN) $(CLIENT)

$(CLIENT): $(OBJDIR)/client.o
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/client.o: client.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(MAIN): $(OBJDIR)/main.o
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/main.o: main.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -f $(OBJDIR)/*.o $(MAIN) $(CLIENT)