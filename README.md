# Calculus in C

In the 1st version of this program, it utilizes **stack** and **queue** data structures to evaluate a mathematical equation in the form of a string. This feature is accomplished using the **Shunting Yard Algorithm**, which is widely used to first order a math expression in the **Reversed-Polish Form** and then evaluate the expression.

Using this feature, the program has the capability to apply **Riemann Sum** for **Integral Approximation** over rectangular input fields.

`Makefile` has different modes to compile the program: normal, for testing, and debug. Run the following commands for their proper use:

  - `make`: Default compiler.
  - `make run`: Runs the output file `a.out` using manual CLI arguments (if none is provided, the program will display needed arguments to run).
  - `make test`: Compile the test file that accesses the test cases, and runs **Shunting Yard Algorithm** for each test example.
  - `make runtest`: Run the test file compiled by `make test`. Displays what portion of the test cases were a pass.
  - `make debug`: Runs the output file `a.out` using the **gdb** compiler for debug. Using this compiler, you can add breakpoints in the program and see where the code breaks.
  - `make clean`: Cleans the output file `a.out`
  - `make cleantest`: Cleans the test output file `test`
  - `make leak`: Compiles the output file `a.out` while checking for leak in memory using **valgrind** compiler.

In the future applications, or development of this project, the same principles can be used for integration of functions more multiple inputs (the program only covers 2-variable functions). Also the integral approximation can be applied over irregular shapes of input region as well.
