CC = gcc
CFLAGS = -m32 -Wall
memtest: memchunk.o test.o
	$(CC) $(CFLAGS) -o memtest memchunk.o test.o

memchunk.o: memchunk.c memchunk.h
	$(CC) $(CFLAGS) -c memchunk.c

test.o: test.c memchunk.h
	$(CC) $(CFLAGS) -c test.c
clean:
	rm memtest *.o
