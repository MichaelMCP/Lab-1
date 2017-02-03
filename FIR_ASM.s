	AREA main, CODE, READONLY
	EXPORT FIR_ASM
FIR_ASM
	;R0 is input x values
	;R1 is output array
	;R2 is b coefficients
	;R3 length of input
	;R4 is counter
	;ADD R4, R4, #4 ;adds 4 to couner to account for N-4
	VLDR.f32 S5, [R2]
	VLDR.f32 S6, [R2, #4]
	VLDR.f32 S7, [R2, #8]
	;LDR R3, [R3] ;take pointer and replace with value
loop
	VLDR.f32 S8, [R0]; Takes x value and puts i register
	ADD R0, R0, #4; Increments pointe to refer to next value
	VMUL.f32 S8, S5, S8; Multiplies coeff b0 and x
	VLDR.f32 S9, [R0]
	ADD R0, R0, #4; Refers to x + 2
	VMUL.f32 S9, S6, S9; multiples coeff b1 and x
	VADD.f32 S8, S8, S9 ;Takes 2nd value and sums with first.
	VLDR.f32 S9, [R0]
	ADD R0, R0, #4; refers to x + 3
	VMUL.f32 S9, S7, S9; multiplies coeff b2 and x
	VADD.f32 S8, S8, S9
	VLDR.f32 S9, [R0]
	ADD R0, R0, #4; refers to x + 4
	VMUL.f32 S9, S6, S9
	VADD.f32 S8, S8, S9
	VLDR.f32 S9, [R0]
	ADD R0, R0, #4; refers to x start of next loop
	VMUL.f32 S9, S5, S9
	VADD.f32 S8, S8, S9; adds the 5th value to the sum
	VSTR.f32 S8, [R1]; Stores the ouput in the output array
	ADD R1, R1, #4
	ADD R4, R4, #1 ;increments counter
	ADD R0, R0, #-16
	CMP R4, R3 ;Checks if end has been reached
	BNE loop; contiues loop if not end
	END