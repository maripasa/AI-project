# Use examples:
# make
# make clean

# Targets
all: bin/SCM_Extractor

bin/SCM_Extractor: ./src/SCM_Extractor.c ./obj/PGM_Operations.o
	gcc -o $@ $^ -I./include

obj/PGM_Operations.o: ./src/PGM_Operations.c ./include/PGM_Operations.h
	gcc -c -o $@ $< -I./include

clean-unix:
	rm -f obj/PGM_Operations.o bin/SCM_Extractor

clean-windows:
	del obj\PGM_Operations.o bin\SCM_Extractor