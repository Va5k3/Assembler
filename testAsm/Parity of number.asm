// Load the number to be checked
@num
D=M

// Check if num % 2 == 0
@2
D=D%A    //This computation does not exist   <--------
@PARITY
D;JEQ // If remainder is 0, the number is even

// If not even, set result = 0 (odd)
@result
M=0
@END
0;JMP

// If even, set result = 1
(PARITY)
@result
M=1

// End of the program
(END)
