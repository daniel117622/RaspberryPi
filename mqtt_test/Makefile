CC = g++
CFLAGS = -Wall -std=c++11

SRCDIR = .
OBJDIR = obj
BINDIR = bin

MAIN = $(BINDIR)/main.out
SERVER = $(BINDIR)/server.out

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

all: $(MAIN) $(SERVER)

$(MAIN): $(OBJDIR)/main.o
	$(CC) $(CFLAGS) -o $@ $^

$(SERVER): $(OBJDIR)/server.o
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJDIR)/*.o $(MAIN) $(SERVER)
