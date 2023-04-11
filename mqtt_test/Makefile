CC = g++
CFLAGS = -Wall -Wextra -Wpedantic -std=c++11
LDFLAGS = 

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

MAIN_SRC = main.cpp
CLIENT_SRC = client.cpp
FRAME_HEADERS = client_handler.hpp frame.hpp frame_write.hpp server.hpp

MAIN_OBJ = $(MAIN_SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
CLIENT_OBJ = $(CLIENT_SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

MAIN_TARGET = $(BIN_DIR)/main
CLIENT_TARGET = $(BIN_DIR)/client 

.PHONY: all clean

all: $(MAIN_TARGET) $(CLIENT_TARGET)

$(MAIN_TARGET): $(MAIN_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(CLIENT_TARGET): $(CLIENT_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(addprefix $(SRC_DIR)/,$(FRAME_HEADERS))
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)