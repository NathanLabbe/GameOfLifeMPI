CFLAGS = -Wall -g -o 

bin/PPAR_TP5_Game: clean obj/PPAR_TP5_Game.o
	gcc $(CFLAGS) bin/PPAR_TP5_Game obj/PPAR_TP5_Game.o

obj/PPAR_TP5_Game.o: src/PPAR_TP5_Game.c
	gcc $(CFLAGS) obj/PPAR_TP5_Game.o -c src/PPAR_TP5_Game.c

clean :
	rm -rf obj bin
	mkdir obj
	mkdir bin

test :
	./bin/PPAR_TP5_Game

