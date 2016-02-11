CC= gcc
CFLAGS= -Wall -g -c -w -std=c99
LFLAGS= -Wall -g

all: shell

shell: shell.o stack.o pipes.o
	$(CC) $(LFLAGS) -o $@ $^

shell.o: shell.c shell.h unifiedHeader.h
	$(CC) $(CFLAGS) -o $@ $<

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -o $@ $<

pipes.o: pipes.c pipes.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o shell