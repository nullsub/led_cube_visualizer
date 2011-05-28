all:
	gcc -pthread -Wall -fPIC -c Impulse.c -o Impulse.o
	gcc -std=gnu99 -c test-libimpulse.c -o test-libimpulse.o
	gcc -pthread -lpulse -lfftw3 -fPIC test-libimpulse.o Impulse.o -o visualizer_server



