# Makefile for SCM_Extractor project

# Use examples:
# make
# make clean

# Directories
BUILD_DIR = ../build
EXE_DIR = ..

# Source files
SRC_FILES = $(wildcard *.c)
PGM_OBJS = $(BUILD_DIR)/PGM_Operations/PGM_Operations.o
EXE_NAME = $(EXE_DIR)/SCM_Extractor.exe

# Targets
all: $(EXE_NAME)

$(EXE_NAME): $(SRC_FILES) $(PGM_OBJS)
	gcc -o $@ $^ -I./PGM_Operations -lm

$(PGM_OBJS): PGM_Operations/PGM_Operations.c PGM_Operations/PGM_Operations.h
	gcc -c -o $@ $< -lm

clean:
	rm -f $(PGM_OBJS) $(EXE_NAME)