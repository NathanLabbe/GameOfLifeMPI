CFLAGS = -Wall -g -o 

bin/PPAR_TP5_GameMPI: clean obj/PPAR_TP5_GameMPI.o
	mpicc $(CFLAGS) bin/PPAR_TP5_GameMPI obj/PPAR_TP5_GameMPI.o

obj/PPAR_TP5_GameMPI.o: src/PPAR_TP5_GameMPI.c
	mpicc $(CFLAGS) obj/PPAR_TP5_GameMPI.o -c src/PPAR_TP5_GameMPI.c

clean :
	rm -rf obj bin
	mkdir obj
	mkdir bin

test :
	mpirun -np 4 ./bin/PPAR_TP5_GameMPI

