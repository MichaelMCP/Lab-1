Area main, CODE, READONLY
	EXPORT FIR_ASM
FIR_ASM
	;R0 is input x values
	;R1 is output array
	;R2 is b coefficients
	;R3 length of input
	;R4 is counter
	ADD R4, R4, #4 ;adds 4 to couner to account for N-4
	VLDR S5, [R2]
	VLDR S6, [R2, #4]
	VLDR S7, [R2, #8]
	VLDR R3, [R3] ;take pointer and replace with value
	loop
	VLDR S8, [R0]; Takes x value and puts i register
	ADD R3, R3, #4; Increments pointe to refer to next value
	MUL S8, S5, S8; Multiplies coeff b0 and x
	VSTR S9, [R0]
	ADD R3, R3, #4; Refers to x + 2
	MUL S9, S6, S9; multiples coeff b1 and x
	ADD S8, S8, S9 ;Takes 2nd value and sums with first.
	VLDR S9, [R0]
	ADD R3, R3, #4; refers to x + 3
	MUL S9, S7, S9; multiplies coeff b2 and x
	ADD S8, S8, S9
	VLDR S9, [R0]
	ADD R3, R3, #4; refers to x + 4
	MUL S9, S6, S9
	ADD S8, S8, S9
	VLDR S9, [R0]
	ADD R3, R3, #4; refers to x start of next loop
	MUL S9, S5, S9
	ADD S8, S8, S9; adds the 5th value to the sum
	VSTR R1, [R8]; Stores the ouput in the output array
	ADD R1, R1, #4
	ADD R4, R4, #1 ;increments counter
	ADD R0, R0, #-16
	CMP R4, R3 ;Checks if end has been reached
	BNE loop; contiues loop if not end
	END