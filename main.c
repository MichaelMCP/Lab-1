#include <stdio.h>
#include <math.h>
#include "FIR_C.h"
#include "arm_math.h"
//#include "test.h"

#define LENGTH	10

int sub_original_from_filter(float* OriginalArray, float* FilteredArray, float* SubtArray, int Length);
float average_cal(float* SubtArray, int Length);
double standard_deviation_cal(float* SubtArray, float average, int Length);
float correlation_coeff_cal(float* OriginalArray, float* FilteredArray, float ori_avg, float filt_avg, double ori_std_deviation, double filt_std_deviation, int Length);

  /**
   * @brief Floating-point vector subtraction.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_sub_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  float32_t * pDst,
  uint32_t blockSize);

  /**
   * @brief  Standard deviation of the elements of a floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
void arm_std_f32(
  float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult);

  /**
   * @brief Correlation of floating-point sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   */
void arm_correlate_f32(
  float32_t * pSrcA,
  uint32_t srcALen,
  float32_t * pSrcB,
  uint32_t srcBLen,
  float32_t * pDst);


int main()
{
	struct FIR_coeff coeff;
	coeff.b0 = 0.1; 
	coeff.b1 = 0.15; 
	coeff.b2 = 0.5; 
	coeff.b3 = 0.15; 
	coeff.b4 = 0.1; 
	
	float input_array[] = {3, 5, 2, 6, 4, 2, 1, 6, 8, 7};
	float output_array[LENGTH];
	
	FIR_C(input_array, output_array, &coeff, LENGTH, 4);
	//FIR_ASM(&input_array, &output_array, &coeff, LENGTH);
	
	int i;
	for(i=0; i<LENGTH; i++) {
		printf("%f\n", output_array[i]); 
	}
	
	return 0;
}

int sub_original_from_filter(float* OriginalArray, float* FilteredArray, float* SubtArray, int Length) {
	int i;
	
	for(i = 0; i < Length; i++) {
		SubtArray[i] = OriginalArray[i] - FilteredArray[i];
	}
	
	return 0;
}

float average_cal(float* SubtArray, int Length) {
	int i;
	float sum = 0;
	
	for(i = 0; i < Length; i++) {
		sum += SubtArray[i];
	}
	
	return sum/Length;
}

double standard_deviation_cal(float* SubtArray, float average, int Length) {
	int i;
	float sum = 0;
	float variance;
	
	for(i = 0; i < Length; i++) {
		sum += (SubtArray[i] - average) * (SubtArray[i] - average);
	}
	
	variance = sum/Length;
	
	return sqrt(variance);
}

float correlation_coeff_cal(float* OriginalArray, float* FilteredArray, float ori_avg, float filt_avg, double ori_std_deviation, double filt_std_deviation, int Length) {
	int i;
	float sum = 0;
	
	for(i = 0; i< Length; i++) {
		sum += (OriginalArray[i] - ori_avg) * (FilteredArray[i] - filt_avg);
	}
	
	sum = sum/(ori_std_deviation * filt_std_deviation);
	
	return sum/(Length - 1);
}

