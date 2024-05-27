IDIR = include/
SRCDIR = src/

CC = gcc
CFLAGS = -g -lncurses -I$(IDIR)
TFLAGS = -I$(SRCDIR)

all: a.out

a.out:
	$(CC) ./src/approx.c $(CFLAGS) -o $@

run:
	./a.out

bebug:
	gdb ./a.out

clean:
	rm a.out

test:
	$(CC) ./tests/tests.c $(CFLAGS) $(TFLAGS) -o $@

runtest:
	./test testdata.txt

debugtest:
	gdb ./test

cleantest:
	rm test