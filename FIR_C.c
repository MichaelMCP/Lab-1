#include "FIR_C.h"
#include <math.h>
//Performs the FIR filtering in C.
int FIR_C(float* InputArray, float* OutputArray, struct FIR_coeff* coeff, int Length, int Order) {
	int input_array_pointer;
	int output_array_pointer = 0;
	int filter_coeff_pointer;
	float sum;
	
	for(input_array_pointer = 0; input_array_pointer < Length; input_array_pointer++) { //Going through all the elements in the input array
		sum = 0;
		for(filter_coeff_pointer = 0; filter_coeff_pointer <= Order; filter_coeff_pointer++) { //Going through the coefficients
			if(filter_coeff_pointer == 0) {
				sum = coeff->b0 * InputArray[input_array_pointer + 4 - filter_coeff_pointer]; //Skipping the first 4 inputs for accuracy 
			}
			else if(filter_coeff_pointer == 1) {
				sum += coeff->b1 * InputArray[input_array_pointer + 4 - filter_coeff_pointer];
			}
			else if(filter_coeff_pointer == 2) {
				sum += coeff->b2 * InputArray[input_array_pointer + 4 - filter_coeff_pointer];
			}
			else if(filter_coeff_pointer == 3) {
				sum += coeff->b3 * InputArray[input_array_pointer + 4 - filter_coeff_pointer];
			}
			else{
				sum += coeff->b4 * InputArray[input_array_pointer + 4 - filter_coeff_pointer];
			}
		}
		
		OutputArray[output_array_pointer] = sum; //After summing, put it to the output array
		output_array_pointer++;
	}
	
	return 0;
}


	