IDIR = include/
SRCDIR = src/

CC = gcc
VCC = valgrind
CFLAGS = -g -lncurses -I$(IDIR)
TFLAGS = -I$(SRCDIR)

all: a.out

a.out:
	$(CC) ./src/approx.c $(CFLAGS) -o $@


log:
	$(VCC) ./src/approx.c $(CFLAGS) -o $@

leak:
	$(VCC) --leak-check=full \
         	--show-leak-kinds=all \
         	--track-origins=yes \
         	--verbose \
         	--log-file=valgrind-out.txt \
         	./src/approx.c $(CFLAGS) -o $@

run:
	./a.out

bebug:
	gdb ./a.out

clean:
	rm a.out

test:
	$(CC) ./tests/tests.c $(CFLAGS) $(TFLAGS) -o $@

logtest:
	$(VCC) -s ./tests/tests.c $(CFLAGS) $(TFLAGS) -o $@

leaktest:
	$(VCC) --leak-check=full \ 
		   	--show-leak-kinds=all \
           	--track-origins=yes \
           	--verbose \
           	--log-file=valgrind-out.txt \
           	./tests/tests.c $(CFLAGS) $(TFLAGS) -o $@

runtest:
	./test testdata.txt

debugtest:
	gdb ./test

cleantest:
	rm test