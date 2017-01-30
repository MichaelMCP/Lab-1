struct FIR_coeff {
	int b0;
	int b1;
	int b2;
	int b3;
	int b4;   
};

int FIR_C(float* InputArray, float* OutputArray, struct FIR_coeff* coeff, int Length, int Order) {
	int input_array_pointer;
	int output_array_pointer = 0;
	int filter_coeff_pointer;
	float sum;
	
	for(input_array_pointer = 0; input_array_pointer < Length; input_array_pointer++) {
		sum = 0;
		for(filter_coeff_pointer = 0; filter_coeff_pointer <= Order; filter_coeff_pointer++) {
			switch(filter_coeff_pointer) {
				case 0:
					sum += coeff->b0 * InputArray[input_array_pointer - filter_coeff_pointer];
					OutputArray[output_array_pointer] = sum;
				
				case 1:
					if(input_array_pointer - filter_coeff_pointer >= 0) {
						sum += coeff->b1 * InputArray[input_array_pointer - filter_coeff_pointer];
					}
					else {
						OutputArray[output_array_pointer] = sum;
						output_array_pointer++;
						break;
					}	
				case 2:
					if(input_array_pointer - filter_coeff_pointer >= 0) {
						sum += coeff->b2 * InputArray[input_array_pointer - filter_coeff_pointer];
					}
					else {
						OutputArray[output_array_pointer] = sum;
						output_array_pointer++;
						break;
					}
				case 3:
					if(input_array_pointer - filter_coeff_pointer >= 0) {
						sum += coeff->b3 * InputArray[input_array_pointer - filter_coeff_pointer];
					}
					else {
						OutputArray[output_array_pointer] = sum;
						output_array_pointer++;
						break;
					}
				case 4:
					if(input_array_pointer - filter_coeff_pointer >= 0) {
						sum += coeff->b4 * InputArray[input_array_pointer - filter_coeff_pointer];
					}
					else {
						OutputArray[output_array_pointer] = sum;
						output_array_pointer++;
						break;
					}
			}
		}
	}
	
	return 0;
}
	