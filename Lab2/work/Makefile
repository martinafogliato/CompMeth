CC = gcc

override CFLAGS += -Wall -mmmx -msse -msse2 -mssse3 -msse4 -mavx2 #-fselective-scheduling -fsel-sched-pipelining -ffast-math -fwhole-program -floop-parallelize-all -funroll-loops -faggressive-loop-optimizations


all: lab2.o 
	$(CC) lab2.o -o lab2 -lm

thread: lab2_thread.o 
	$(CC) lab2_thread.o -o lab2_thread -lm -lpthread


clean:
	rm -f lab2.o 

