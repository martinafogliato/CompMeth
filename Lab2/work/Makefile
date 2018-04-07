CC = gcc

CFLAGS = -Wall -mmmx -msse -msse2 -mssse3 -msse4 -mavx2


all: lab2.o fixed_point.o
	$(CC) lab2.o fixed_point.o -o lab2 -lm

clean:
	rm -f *.o 

