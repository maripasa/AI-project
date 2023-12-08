# Use examples:
# make
# make clean

# $@ é o alvo
# $^ é o pre-requisito

# EXEMPLO -> output.txt: input1.txt input2.txt input3.txt
# $@ -> output.txt
# $^ -> input1.txt input2.txt input3.txt

# make comum
all: bin/SCM_Extractor

# make SCM_Extractor
bin/SCM_Extractor: ./src/SCM_Extractor.c ./obj/PGM_Operations.o ./obj/SCM_Util.o
	gcc -o $@ $^ -I./include

# make PGM_Operations
obj/PGM_Operations.o: ./src/PGM_Operations.c ./include/PGM_Operations.h
	gcc -c -o $@ $< -I./include

# make SCM_Util
obj/SCM_Util.o: ./src/SCM_Util.c ./include/SCM_Util.h
	gcc -c -o $@ $< -I./include

# clean para unix e windows
clean-unix:
	rm -f obj/PGM_Operations.o obj/SCM_Util.o bin/SCM_Extractor
clean-windows:
	del obj/PGM_Operations.o obj/SCM_Util.o bin/SCM_Extractor
