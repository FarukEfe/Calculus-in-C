IDIR = include/

CC = gcc
CFLAGS = -g -lncurses -I$(IDIR)

all: a.out

a.out:
	$(CC) ./src/approx.c $(CFLAGS) -o $@

run:
	./output

clean:
	rm output