struct FIR_coeff {
	float b0;
	float b1;
	float b2;
	float b3;
	float b4;   
};
//Defines the structure of the coefficients for the FIR filter.
int FIR_C(float* InputArray, float* OutputArray, struct FIR_coeff* coeff, int Length, int Order);