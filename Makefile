CC=gcc
CFLAGS=-Wall -s

.PHONY: vm

clean:
	rm *.o vm

vm:
	$(CC) -o vm main.c $(CFLAGS)
