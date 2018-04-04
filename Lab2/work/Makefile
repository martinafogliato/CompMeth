CC = gcc

CFLAGS = -Wall -mmmx -msse -msse2 -mssse3 -msse4

# Utility routines
UTIL_OBJS += lab2.o 

#

all: fft

OBJ = $(UTIL_OBJS)
$(OBJ) : %.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

ffttest: $(OBJ) lab2.o
	$(CC)  $(OBJ) lab2.o -o lab2

clean:
	rm -f *.o 

