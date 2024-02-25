SRC_DIR = src
BUILD_DIR = build/debug
CC = gcc
SRC_FILES = $(shell find $(SRC_DIR) -name '*.c')
OBJ_NAME = play
INCLUDE_PATHS = -I include/SDL2 -I include/SDL2_image -I include/SDL2_ttf
LIBRARY_PATHS = -L lib/SDL2 -L lib/SDL2_image -L lib/SDL2_ttf
COMPILER_FLAGS = -std=c11 -Wall -O0 -g
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)