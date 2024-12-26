// Initialize fib0 = 0
@0
D=A
@fib0
M=D

// Initialize fib1 = 1
@1
D=A
@fib1
M=D

// Set the counter for the number of iterations (4 Fibonacci numbers)
@4
D=A
@count
M=D

// Start of the loop
(FIB_LOOP)
// Check if the counter has reached 0
@count
D=M
@0
D=D-A
@END
D;JEQ // If counter == 0, jump to END

// Compute fib2 = fib1 + fib0
@fib1
D=M
@fib0
D=D+M
@fib2
M=D

// Shift fib1 to fib0
@fib1
D=M
@fib0
M=D

// Shift fib2 to fib1
@fib2
D=M
@fib1
M=D

// Decrement the counter
@count
M=M-1

// Repeat the loop
@FIB_LOOP
0;JMP

// End of the program
(END)
