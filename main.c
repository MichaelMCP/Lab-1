#include <stdio.h>
#include <math.h>
#include "arm_math.h"
#include "FIR_C.h"
#include "FIR_CMSIS.h"
#include "test.h"

#define LENGTH	20

int sub_original_from_filter(float* OriginalArray, float* FilteredArray, float* SubtArray, int Length);
float average_cal(float* SubtArray, int Length);
float standard_deviation_cal(float* SubtArray, float average, int Length);
float correlation_coeff_cal(float* OriginalArray, float* FilteredArray, float ori_avg, float filt_avg, float ori_std_deviation, float filt_std_deviation, int Length);

int main()
{
	struct FIR_coeff coeff; //Structure defines filter coefficients.
	coeff.b0 = 0.1; 
	coeff.b1 = 0.15; 
	coeff.b2 = 0.5; 
	coeff.b3 = 0.15; 
	coeff.b4 = 0.1; 
	
	//float input_array[] = {3, 5, 2, 6, 4, 2, 1, 6, 8, 7};
	float output_array[LENGTH];
	
	arm_fir_instance_f32 cmsis_instance;
	
	float coeff_array[] = {0.1, 0.15, 0.5, 0.15, 0.1}; //used for the CMSIS input only.
	float pState_array[LENGTH + 5]; //Used for the CMSIS input.
	
	arm_fir_init_f32(&cmsis_instance, 5, coeff_array, pState_array, LENGTH);
	
	FIR_C(input_array, output_array, &coeff, LENGTH, 4);
	//FIR_ASM(&input_array, &output_array, &coeff, LENGTH);
	//arm_fir_f32(&cmsis_instance, input_array, output_array, LENGTH);
	int j = 0 + 1;
	int i;
	//Shifts output to ensure accuracy of part 2 methods.
	float shifted_output_array[LENGTH];
	for(i=0; i<LENGTH; i++) {
		if(i<4) {
			shifted_output_array[i] = 0;
		}
		else {
			shifted_output_array[i] = output_array[i - 4];
		}
	}
	
	printf("\nOriginal Array:\n");
	for(i=0; i<LENGTH; i++) {
		printf("%f\n", input_array[i]); 
	}
	
	//outputs the results of all calculations done.
	/*printf("\nFiltered Array:\n");
	for(i=0; i<LENGTH; i++) {
		printf("%f\n", output_array[i]); 
	}*/
	
	printf("\nFiltered Array:\n");
	for(i=0; i<LENGTH; i++) {
		printf("%f\n", shifted_output_array[i]); 
	}
	
	float subt_array[LENGTH];
	//sub_original_from_filter(input_array, shifted_output_array, subt_array, LENGTH);
	arm_sub_f32(input_array, shifted_output_array, subt_array, LENGTH);
	
	printf("\nSubt Array:\n");
	for(i=0; i<LENGTH; i++) {
		printf("%f\n", subt_array[i]); 
	}
	
	float subt_avg;
	//subt_avg = average_cal(subt_array, LENGTH);
	arm_mean_f32(subt_array, LENGTH, &subt_avg);
	
	printf("\nAverage of difference: %f\n", subt_avg);
	
	float subt_std_deviation;

	subt_std_deviation	= standard_deviation_cal(subt_array, subt_avg, LENGTH);
	//arm_std_f32(subt_array, LENGTH, &subt_std_deviation);
	
	printf("\nStandard deviation is: %f\n", subt_std_deviation);
	
	float ori_avg = average_cal(input_array, LENGTH);
	float filt_avg = average_cal(output_array, LENGTH);
	float ori_std_deviation;
	float filt_std_deviation;
	
	//ori_std_deviation = standard_deviation_cal(input_array, ori_avg, LENGTH);
	arm_std_f32(input_array, LENGTH, &ori_std_deviation);
	
	//filt_std_deviation = standard_deviation_cal(output_array, filt_avg, LENGTH);
	arm_std_f32(output_array, LENGTH, &filt_std_deviation);
	
	float correlation_coeff;
	
	//correlation_coeff = correlation_coeff_cal(input_array, output_array, ori_avg, filt_avg, ori_std_deviation, filt_std_deviation, LENGTH);
	arm_correlate_f32(input_array, LENGTH, output_array, LENGTH, &correlation_coeff);
	
	printf("\nCorrelation Coefficient is: %f\n", correlation_coeff);
	
	return 0;
}

//Subtracts the elements from the original stream and the filtered one
int sub_original_from_filter(float* OriginalArray, float* FilteredArray, float* SubtArray, int Length) { 
	int i;
	
	for(i = 0; i < Length; i++) {
		SubtArray[i] = OriginalArray[i] - FilteredArray[i];
	}
	
	return 0;
}

//Calculates the average
float average_cal(float* SubtArray, int Length) {
	int i;
	float sum = 0;
	
	for(i = 0; i < Length; i++) {
		sum += SubtArray[i];
	}
	
	return sum/Length;
}

//Calculates the standard deviation
float standard_deviation_cal(float* SubtArray, float average, int Length) {
	int i;
	float sum = 0;
	float variance;
	
	for(i = 0; i < Length; i++) {
		sum += powf((SubtArray[i] - average), 2);
	}
	
	variance = sum/Length;
	
	return sqrtf(variance);
}

//Calculates the correlation coefficient
float correlation_coeff_cal(float* OriginalArray, float* FilteredArray, float ori_avg, float filt_avg, float ori_std_deviation, float filt_std_deviation, int Length) {
	int i;
	float sum = 0;
	
	for(i = 0; i< Length; i++) {
		sum += (OriginalArray[i] - ori_avg) * (FilteredArray[i] - filt_avg);
	}
	
	sum = sum/(ori_std_deviation * filt_std_deviation);
	
	return sum/(Length - 1);
}

