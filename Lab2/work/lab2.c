// Include files for SSE4
#include <emmintrin.h>
#include <xmmintrin.h>
#include <stdint.h>
#include <tmmintrin.h>
#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "time_meas.h"

#define NUM_TESTS 1000000
#define _DEBUGTIME_
//#define _DEBUGARRAY_
#define _SSE4_
//#define _AVX2_


int16_t FIX_MPY(int16_t x, int16_t y);
int16_t SAT_ADD16(int16_t x,int16_t y);
#ifdef _COMPLEX_
inline void cmult(__m128i a,__m128i b, __m128i *re32, __m128i *im32);
inline __m128i cpack(__m128i xre,__m128i xim);
#endif

void componentwise_multiply_real_scalar(int16_t *x,int16_t *y,int16_t *z,uint16_t N);

#ifdef _SSE4_
void componentwise_multiply_real_sse4(int16_t *x,int16_t *y,int16_t *z,uint16_t N);
#endif

#ifdef _AVX2_
void componentwise_multiply_real_avx2(int16_t *x,int16_t *y,int16_t *z,uint16_t N);
#endif

void run_tests(int16_t *x,int16_t *y,int16_t *z,uint16_t N);



int main(int argc, char* argv[]) {

  uint16_t N = atoi(argv[1]);
  int16_t * array_x, * array_y, * array_z;
  int i;

	srand(time(NULL)+getpid());

	if(argc != 2){
		printf("usage : lab2 <array_length>\n");
		exit(-1);
	}

	array_x = malloc((N+32) * sizeof(int16_t));
	array_y = malloc((N+32) * sizeof(int16_t));
	array_z = malloc((N+32) * sizeof(int16_t));

	for (i=0; i<N; i++){
		array_x[i]=rand();
		array_y[i]=rand();
	}

  #ifdef _DEBUGARRAY_
	for(i=0; i<N; i++){
		printf("x[%d] : %d	y[%d] : %d\n", i, array_x[i], i, array_y[i]);
	}
  #endif

  run_tests(array_x, array_y, array_z, N);

	free(array_x);
	free(array_y);
	free(array_z);

	return 0;
}


void run_tests(int16_t *x,int16_t *y,int16_t *z,uint16_t N){
  time_stats_t time_struct;
  int i;
  reset_meas(&time_struct);

    for(i=1; i<NUM_TESTS; i++){
    start_meas(&time_struct);
    componentwise_multiply_real_scalar(x, y, z, N);
    stop_meas(&time_struct);
  }
  #ifdef _DEBUGARRAY_
  for(i=0; i<N; i++){
  	printf("z[%d] : %d\n", i, z[i]);
  }
  #endif

  #ifdef _DEBUGTIME_
  printf("total time : %lld	time average: %lld\n", time_struct.diff, time_struct.diff/NUM_TESTS);
  #endif

  #ifdef _SSE4_
  reset_meas(&time_struct);

  for(i=0; i<NUM_TESTS; i++){
    start_meas(&time_struct);
    componentwise_multiply_real_sse4(x, y, z, N);
    stop_meas(&time_struct);
  }
  #ifdef _DEBUGARRAY_
  for(i=0; i<N; i++){
    printf("z[%d] : %d\n", i, z[i]);
  }
  #endif

  #ifdef _DEBUGTIME_
  printf("total time : %lld	time average: %lld\n", time_struct.diff, time_struct.diff/NUM_TESTS);
  #endif

  #endif

  #ifdef _AVX2_

  reset_meas(&time_struct);

  for(i=0; i<NUM_TESTS; i++){
    start_meas(&time_struct);
    componentwise_multiply_real_avx2(x, y, z, N);
    stop_meas(&time_struct);
  }

  #ifdef _DEBUGPRINT_
  for(i=0; i<N; i++){
    printf("z[%d] : %d\n", i, z[i]);
  }
  #endif

  #ifdef _DEBUGTIME_
  printf("total time : %lld	time average: %lld\n", time_struct.diff, time_struct.diff/NUM_TESTS);
  #endif

  #endif
}

#ifdef _COMPLEX_

__m128i mmtmpb;
extern __m128i* reflip;

inline void cmult(__m128i a,__m128i b, __m128i *re32, __m128i *im32) {

  mmtmpb    = _mm_sign_epi16(b,*(__m128i*)reflip); //Negates packed words in a if corresponding sign in b is less than zero. Interpreting a, b, and r as arrays of signed 16-bit integers
  *re32     = _mm_madd_epi16(a,mmtmpb); //Multiplies 128x128
  mmtmpb    = _mm_shufflelo_epi16(b,_MM_SHUFFLE(2,3,0,1)); //Shuffles the lower four signed or unsigned 16-bit integers in a as specified by imm. The shuffle value, imm, must be an immediate. _MM_SHUFFLE(2, 3, 0, 1) permutes [a3, a2, a1, a0] to [a2, a3, a0, a1].
  mmtmpb    = _mm_shufflehi_epi16(mmtmpb,_MM_SHUFFLE(2,3,0,1)); //Shuffles the upper four signed or unsigned 16-bit integers in a as specified by imm. The shuffle value, imm, must be an immediate.
  *im32  = _mm_madd_epi16(a,mmtmpb);
}

__m128i cpack_tmp1,cpack_tmp2;
inline __m128i cpack(__m128i xre,__m128i xim) {

  cpack_tmp1 = _mm_unpacklo_epi32(xre,xim); //Unpack and interleave 32-bit integers from the low half of a and b, and store the results in dst.
  cpack_tmp1 = _mm_srai_epi32(cpack_tmp1,15); //Shift packed 32-bit integers in 'a' right by imm while shifting in sign bits, and store the results in dst.
  cpack_tmp2 = _mm_unpackhi_epi32(xre,xim);
  cpack_tmp2 = _mm_srai_epi32(cpack_tmp2,15);
  return(_mm_packs_epi32(cpack_tmp1,cpack_tmp2)); //Convert packed 32-bit integers from a and b to packed 16-bit integers using signed saturation

}

#endif


void componentwise_multiply_real_scalar(int16_t *x,int16_t *y,int16_t *z,uint16_t N) {
	int i;

	for(i=0; i<N; i++){
		z[i] = FIX_MPY(x[i], y[i]);
	}

}

#ifdef _SSE4_
void componentwise_multiply_real_sse4(int16_t *x,int16_t *y,int16_t *z,uint16_t N) {

	__m128i *x128 = (__m128i *)x;
	__m128i *y128 = (__m128i *)y;
	__m128i *z128 = (__m128i *)z;
	int i;

	for(i=0; i<ceil(N/8.0); i++){
		z128[i] = _mm_mulhrs_epi16(x128[i], y128[i]);
	}

}
#endif

#ifdef _AVX2_
void componentwise_multiply_real_avx2(int16_t *x,int16_t *y,int16_t *z,uint16_t N) {


	__m256i *x256 = (__m256i *)x;
	__m256i *y256 = (__m256i *)y;
	__m256i *z256 = (__m256i *)z;
	int i;

	for(i=0; i<ceil(N/16.0); i++){
		printf("hei\n");
		z256[i] = _mm256_mullo_epi16(x256[i], y256[i]);
	}

}
#endif
