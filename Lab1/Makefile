CC = gcc

CFLAGS =

# Utility routines
UTIL_OBJS += taus.o fixed_point.o rangen_double.o

#

all: fft

OBJ = $(UTIL_OBJS)
$(OBJ) : %.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

fft.o: fft.c
	$(CC)  -c fft.c -o fft.o $(CFLAGS)

fft: $(OBJ) fft.o
	$(CC)  $(OBJ) fft.o -o fft -lm $(CFLAGS)

clean:
	rm -f *.o
