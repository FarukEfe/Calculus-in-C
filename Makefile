### MARK: MAKEFILE VARIABLES

IDIR = include/
SRCDIR = src/
PLOTDIR = /usr/local/bin/plplot-5.15.0 # Replace this line with the location of plplot installed in your os

CC = gcc
VCC = valgrind
CFLAGS = -g -lm -lncurses -I$(IDIR)
PFLAGS = -I$(PLOTDIR)
TFLAGS = -I$(SRCDIR)

all: a.out

### MARK: COMMANDS FOR APPROX.C

# Compile integral approximator
a.out:
	$(CC) ./src/approx.c $(CFLAGS) -o $@

# Use valgrind compiler for integral approximator
log:
	$(VCC) ./src/approx.c $(CFLAGS) -o $@

# Get full leak report for integral approximator
leak:
	$(VCC) --leak-check=full \
         	--show-leak-kinds=all \
         	--track-origins=yes \
         	--verbose \
         	--log-file=valgrind-out.txt \
         	./src/approx.c $(CFLAGS) -o $@

# Run integral approximator (unused for now)
run:
	./a.out

# Run integral approximator in gdb debug (unused for now)
debug:
	gdb ./a.out

# Clean integral approximator build
clean:
	rm a.out

### MARK: TESTING OF OPERATOR.C

# Compile tests for operator.c
test:
	$(CC) ./tests/tests.c $(CFLAGS) $(TFLAGS) -o $@

# Run test build for operator.c
runtest:
	./test testdata.txt

# Clean test build for operator.c
cleantest:
	rm test

### MARK: COMMANDS FOR PLPLOT BUILD

plot:
	$(CC) ./src/approx.c $(CFLAGS) $(PFLAGS) -o $@