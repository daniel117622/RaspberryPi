CC = g++
CFLAGS = -Wall -Wextra -Wpedantic -std=c++11
LDFLAGS = 

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS = $(OBJS:%.o=%.d)

TARGET = $(BIN_DIR)/server

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MM -MT '$(OBJ_DIR)/$(notdir $(<:%.cpp=%.o))' $< -MF $@

-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
