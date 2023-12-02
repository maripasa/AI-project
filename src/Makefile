# Makefile for SCM_Extractor project

# Use examples:

# make
# make PGM_Operations.o
# make SCM_Extractor.exe
# make clean

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -pedantic

# Directories
SRC_DIR = .
BUILD_DIR = ../build
EXE_DIR = ..

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
PGM_OBJS = $(BUILD_DIR)/PGM_Operations/PGM_Operations.o
EXE_NAME = $(EXE_DIR)/SCM_Extractor.exe

# Targets
all: $(EXE_NAME)

$(EXE_NAME): $(SRC_FILES) $(PGM_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -I$(SRC_DIR)/PGM_Operations -lm

$(PGM_OBJS): $(SRC_DIR)/PGM_Operations/PGM_Operations.c $(SRC_DIR)/PGM_Operations/PGM_Operations.h
	$(CC) $(CFLAGS) -c -o $@ $< -lm

clean:
	rm -f $(PGM_OBJS) $(EXE_NAME)