#CC = clang++
CC = g++
CFLAGS = --std=c++14 -O0
LFLAGS = -lpthread

BIN_DIR = ./bin
SRC_DIR = ./src
BLD_DIR = ./build

EXT=.cpp
EXE=main

SRC_FIL = $(wildcard $(SRC_DIR)/*$(EXT))
OBJ_FIL = $(patsubst $(SRC_DIR)/%$(EXT),$(BLD_DIR)/%.o,$(SRC_FIL))

all: dirs $(BIN_DIR)/$(EXE)

dirs: $(BIN_DIR) $(BLD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BLD_DIR):
	mkdir -p $(BLD_DIR)

$(BIN_DIR)/$(EXE): $(OBJ_FIL)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$(EXE) $(LFLAGS) 

$(OBJ_FIL) : $(BLD_DIR)/%.o : $(SRC_DIR)/%$(EXT)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BLD_DIR)/*
	rm -f $(BIN_DIR)/$(EXE)
