CFLAGS = -Wall -g -o 

bin/Shortening: clean obj/Shortening.o
	mpicc $(CFLAGS) bin/Shortening obj/Shortening.o

obj/Shortening.o: src/Shortening.c
	mpicc $(CFLAGS) obj/Shortening.o -c src/Shortening.c

clean :
	rm -rf obj bin
	mkdir obj
	mkdir bin

test :
	mpirun -np 4 ./bin/Shortening

