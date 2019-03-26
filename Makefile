CC = gcc

CFLAGS = -lm -o example.out

example: example.c
	$(CC) $(CFLAGS) example.c

clean:
	rm -f example.out

