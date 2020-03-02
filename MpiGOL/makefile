CFLAGS = -Wall -g -o 

bin/PPAR_TP5_GameMPI: clean obj/PPAR_TP5_GameMPI.o
	gcc $(CFLAGS) bin/PPAR_TP5_GameMPI obj/PPAR_TP5_GameMPI.o

obj/PPAR_TP5_GameMPI.o: src/PPAR_TP5_GameMPI.c
	gcc $(CFLAGS) obj/PPAR_TP5_GameMPI.o -c src/PPAR_TP5_GameMPI.c

clean :
	rm -rf obj bin
	mkdir obj
	mkdir bin

test :
	./bin/PPAR_TP5_GameMPI

