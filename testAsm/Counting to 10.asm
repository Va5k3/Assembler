// Initialize i = 0 and sum = 0
@i
M=0
@sum
M=0

// Start of the loop
(LOOP)
// Load i into D
@i
D=M
// Check if i == 10
@10
D=D-A
@END
D;JEQ // If i == 10, jump to END

// Add i to sum
@sum
M=M+D

// Increment i
@i
M=M+1

// Repeat the loop
@LOOP
0;JMP

// End of the program
(END)
@END
0;JMP
