CC = clang++
#CC = g++
FLAGS = --std=c++14 -O0

BIN_DIR = ./bin
SRC_DIR = ./src
BLD_DIR = ./build

EXT=.cpp

SRC_FIL = $(wildcard $(SRC_DIR)/*$(EXT))
OBJ_FIL = $(patsubst $(SRC_DIR)/%$(EXT),$(BLD_DIR)/%.o,$(SRC_FIL))

all: dirs $(BIN_DIR)/main

dirs: $(BIN_DIR) $(BLD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BLD_DIR):
	mkdir -p $(BLD_DIR)

$(BIN_DIR)/main: $(OBJ_FIL)
	$(CC) $(FLAGS) $(LDFLAGS) $^ -o $(BIN_DIR)/main

$(OBJ_FIL) : $(BLD_DIR)/%.o : $(SRC_DIR)/%$(EXT)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(BLD_DIR)/*
	rm -f $(BIN_DIR)/main
