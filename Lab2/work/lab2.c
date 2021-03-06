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

#define NUM_TESTS 10000
//#define _DEBUGTIME_
//#define _DEBUGARRAY_
#define _SSE4_
#define _AVX2_
//#define _AVX512_
#define _MATLAB_
//#define _COMPLEX_

int16_t volatile * z;

void print128_num(__m128i var);


 int16_t FIX_MPY(int16_t x, int16_t y){

  return ((int16_t)(((int32_t)x * (int32_t)y)>>15));

}

int16_t SAT_ADD16(int16_t x,int16_t y) {
  if ((int32_t)x + (int32_t)y > 32767)
    return(32767);
  else if ((int32_t)x + (int32_t)y < -32767)
    return(-32768);
  else
    return(x+y);
}

#ifndef _COMPLEX_

  void run_tests(int16_t *x,int16_t *y,int16_t volatile *z,uint16_t N, uint16_t Nmin);
  void componentwise_multiply_real_scalar(int16_t *x,int16_t *y,int16_t volatile *z,uint16_t N);
  #ifdef _SSE4_
   void componentwise_multiply_real_sse4(int16_t *x,int16_t *y,int16_t volatile *z,uint16_t N);
  #endif

  #ifdef _AVX2_
   void componentwise_multiply_real_avx2(int16_t *x,int16_t *y,int16_t volatile *z,uint16_t N);
  #endif

  #ifdef _AVX512_
   void componentwise_multiply_real_avx512(int16_t *x, int16_t *y, int16_t *z, uint16_t N);
  #endif

#else
  const static int16_t reflip[32]  __attribute__((aligned(32))) = {1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1};
  void run_complex_tests(int16_t * x, int16_t * y, int16_t volatile * z, uint16_t N, uint16_t Nmin);
  void componentwise_multiply_complex_scalar(int16_t *x, int16_t *y, int16_t volatile *z, uint16_t N);
  void componentwise_multiply_complex_sse4(int16_t *x, int16_t *y, int16_t volatile *z, uint16_t N);
  void componentwise_multiply_complex_avx2(int16_t *x, int16_t *y, int16_t volatile *z, uint16_t N);
  /*
  inline void cmult(__m128i a,__m128i b, __m128i *re32, __m128i *im32);
  inline __m128i cpack(__m128i xre,__m128i xim);
  */
#endif


int main(int argc, char* argv[]) {


  int i;
  int16_t * x, * y;

	srand(time(NULL)+getpid());

	if(argc != 3){
		printf("usage : lab2 <array_length_min> <array_length_max>\n");
		exit(-1);
	}

    uint16_t N = atoi(argv[2]);
    uint16_t Nmin = atoi(argv[1]);
/*
  if((N-Nmin)%2!=0) {
    printf("Number of elements in the array must be even.\n");
    exit(-1);
  }
*/

	x = aligned_alloc(32, (N+32) * sizeof(int16_t));
	y = aligned_alloc(32, (N+32) * sizeof(int16_t));
	z = aligned_alloc(32, (N+32) * sizeof(int16_t));

	for (i=0; i<N; i++){
		x[i]=rand();
		y[i]=rand();
	}

  #ifdef _DEBUGARRAY_
	for(i=0; i<N; i++){
		printf("x[%d] : %d	y[%d] : %d\n", i, x[i], i, y[i]);
	}
  #endif

  #ifndef _COMPLEX_
    run_tests(x, y, z, N, Nmin);
  #else
    run_complex_tests(x, y, z, N, Nmin);
  #endif

	free((void *)x);
	free((void *)y);
	free((void *)z);

	return 0;
}

#ifndef _COMPLEX_
 void run_tests(int16_t * x, int16_t * y, int16_t volatile * z, uint16_t N, uint16_t Nmin){

  int i, j;
  time_stats_t time_struct;

  for(j=Nmin; j<N; j++){
	  reset_meas(&time_struct);

	  for(i=1; i<NUM_TESTS; i++){
		start_meas(&time_struct);
		componentwise_multiply_real_scalar(x, y, z, j);
		stop_meas(&time_struct);
	  }
	  #ifdef _DEBUGARRAY_
	  for(i=0; i<j; i++){
		printf("z[%d] : %d\n", i, z[i]);
	  }
	  #endif

	  #ifdef _DEBUGTIME_
	  printf("test : SCALAR	total time : %lld	time average: %lld	N : %d\n", time_struct.diff, time_struct.diff/NUM_TESTS, j);
	  #endif

	  #ifdef _MATLAB_
	  printf("%lld %d ", time_struct.diff, j);

	  #if !defined(_SSE4_) & !defined(_AVX2_) & !defined(_AVX512_)
	  printf("\n");
	  #endif

	  #endif

	  #ifdef _SSE4_
	  reset_meas(&time_struct);

	  for(i=0; i<NUM_TESTS; i++){
		start_meas(&time_struct);
		componentwise_multiply_real_sse4(x, y, z, j);
		stop_meas(&time_struct);
	  }
	  #ifdef _DEBUGARRAY_
	  for(i=0; i<j; i++){
		printf("z[%d] : %d\n", i, z[i]);
	  }
	  #endif

	  #ifdef _DEBUGTIME_
	  printf("test : SSE4	total time : %lld	time average: %lld	N : %d\n", time_struct.diff, time_struct.diff/NUM_TESTS, j);
	  #endif

	  #ifdef _MATLAB_
	  printf("%lld %d ", time_struct.diff, j);

	  #if !defined(_AVX2_) & !defined(_AVX512_)
	  printf("\n");
	  #endif

	  #endif

	  #endif

	  #ifdef _AVX2_

	  reset_meas(&time_struct);

	  for(i=0; i<NUM_TESTS; i++){
		start_meas(&time_struct);
		componentwise_multiply_real_avx2(x, y, z, j);
		stop_meas(&time_struct);
	  }

	  #ifdef _DEBUGARRAY_
	  for(i=0; i<j; i++){
		printf("z[%d] : %d\n", i, z[i]);
	  }
	  #endif

	  #ifdef _DEBUGTIME_
	  printf("test : AVX2	total time : %lld	time average: %lld	N : %d\n", time_struct.diff, time_struct.diff/NUM_TESTS, j);
	  #endif

	  #ifdef _MATLAB_
	  printf("%lld %d", time_struct.diff, j);
	  #endif

	  #ifndef _AVX512_
	  printf("\n");
	  #endif

	  #endif

	  #ifdef _AVX512_

	  reset_meas(&time_struct);

	  for(i=0; i<NUM_TESTS; i++){
		start_meas(&time_struct);
		componentwise_multiply_real_avx512(x, y, z, j);
		stop_meas(&time_struct);
	  }

	  #ifdef _DEBUGPRINT_
	  for(i=0; i<j; i++){
		printf("z[%d] : %d\n", i, z[i]);
	  }
	  #endif

	  #ifdef _DEBUGTIME_
	  printf("test : AVX512	total time : %lld	time average: %lld	N : %d\n", time_struct.diff, time_struct.diff/NUM_TESTS, j);
	  #endif

	  #ifdef _MATLAB_
	  printf("%lld %d\n", time_struct.diff, j);
	  #endif

	  #endif

  }
}

#else

void run_complex_tests(int16_t * x, int16_t * y, int16_t volatile * z, uint16_t N, uint16_t Nmin){

 int i, j;
 time_stats_t time_struct;

 for(j=Nmin; j<N; j++){
   reset_meas(&time_struct);

   for(i=1; i<NUM_TESTS; i++){
   start_meas(&time_struct);
   componentwise_multiply_complex_scalar(x, y, z, j);
   stop_meas(&time_struct);
   }
   #ifdef _DEBUGARRAY_
   for(i=0; i<j; i++){
   printf("z[%d] : %d\n", i, z[i]);
   sleep(1);
   }
   #endif

   #ifdef _DEBUGTIME_
   printf("complex test : SCALAR	total time : %lld	time average: %lld	N : %d\n", time_struct.diff, time_struct.diff/NUM_TESTS, j);
   #endif

   #ifdef _MATLAB_
   printf("%lld %d ", time_struct.diff, j);

   #if !defined(_SSE4_) & !defined(_AVX2_)
   printf("\n");
   #endif

   #endif

   #ifdef _SSE4_
   reset_meas(&time_struct);

   for(i=0; i<NUM_TESTS; i++){
   start_meas(&time_struct);
   componentwise_multiply_complex_sse4(x, y, z, j);
   stop_meas(&time_struct);
   }
   #ifdef _DEBUGARRAY_
   for(i=0; i<j; i++){
   printf("z[%d] : %d\n", i, z[i]);
   sleep(1);
   }
   #endif

   #ifdef _DEBUGTIME_
   printf("complex test : SSE4	total time : %lld	time average: %lld	N : %d\n", time_struct.diff, time_struct.diff/NUM_TESTS, j);
   #endif

   #ifdef _MATLAB_
   printf("%lld %d ", time_struct.diff, j);

   #if !defined(_AVX2_)
   printf("\n");
   #endif

   #endif

   #endif

   #ifdef _AVX2_

   reset_meas(&time_struct);

   for(i=0; i<NUM_TESTS; i++){
   start_meas(&time_struct);
   componentwise_multiply_complex_avx2(x, y, z, j);
   stop_meas(&time_struct);
   }

   #ifdef _DEBUGARRAY_
   for(i=0; i<j; i++){
   printf("z[%d] : %d\n", i, z[i]);
   sleep(1);
   }
   #endif

   #ifdef _DEBUGTIME_
   printf("complex test : AVX2	total time : %lld	time average: %lld	N : %d\n", time_struct.diff, time_struct.diff/NUM_TESTS, j);
   #endif

   #ifdef _MATLAB_
   printf("%lld %d\n", time_struct.diff, j);
   #endif

   #endif

}
}

#endif

#ifdef _COMPLEX_
/*
__m128i mmtmpb;

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
*/

void componentwise_multiply_complex_scalar(int16_t *x,int16_t *y,int16_t volatile *z,uint16_t N) {
 int i;

 for(i=0; i<N; i+=2){

   z[i] = FIX_MPY(x[i], y[i]);
   z[i] = SAT_ADD16(FIX_MPY(x[i+1], -y[i+1]), z[i]);
   z[i+1] = FIX_MPY(x[i+1], y[i]);
   z[i+1] SAT_ADD16(FIX_MPY(x[i], y[i+1]), z[i]);

 }
}

void componentwise_multiply_complex_sse4(int16_t *x,int16_t *y,int16_t volatile *z,uint16_t N) {

 __m128i *x128 = (__m128i *)x;
 __m128i *y128 = (__m128i *)y;
 __m128i *z128 = (__m128i *)z;
 int i;
 __m128i z128_im, z128_tmp_lo, z128_tmp_hi;

 for(i=0; i<ceil(N/8.0); i++){
     //real part
   z128[i] = _mm_madd_epi16(x128[i], _mm_sign_epi16(y128[i], *(__m128i *)reflip)); //invert signs of y according to reflip, then multiply and add

     //imaginary part
   z128_im = _mm_madd_epi16(x128[i], _mm_shufflelo_epi16(y128[i],_MM_SHUFFLE(2, 3, 0, 1))); //shuffle y[i] and y[i+1], then multiply and add
   z128_tmp_lo = _mm_unpacklo_epi32(z128[i], z128_im); //interleave 32 bits of real part with 32 bits of imaginary part (low part)
   z128_tmp_hi = _mm_unpackhi_epi32(z128[i], z128_im); //interleave 32 bits of real part with 32 bits of imaginary part (high part)
   z128[i] = _mm_srai_epi32(z128_tmp_lo, 15); //shift each 32 bits group by 15 bits (Q15)
   z128_im = _mm_srai_epi32(z128_tmp_hi, 15);
   z128[i] = _mm_packs_epi32(z128[i], z128_im); //pack together real and imaginary part
 }
}

void componentwise_multiply_complex_avx2(int16_t *x,int16_t *y,int16_t volatile *z, uint16_t N) {

  __m256i *x256 = (__m256i *)x;
  __m256i *y256 = (__m256i *)y;
  __m256i *z256 = (__m256i *)z;
  int i;
  __m256i z256_im, z256_tmp_lo, z256_tmp_hi;
  for(i=0; i<ceil(N/16.0); i++){

    //real part
  z256[i] = _mm256_madd_epi16(x256[i], _mm256_sign_epi16(y256[i], *(__m256i *)reflip));

    //imaginary part
  z256_im = _mm256_madd_epi16(x256[i], _mm256_shufflelo_epi16(y256[i],_MM_SHUFFLE(2, 3, 0, 1)));
  z256_tmp_lo = _mm256_unpacklo_epi32(z256[i], z256_im);
  z256_tmp_hi = _mm256_unpackhi_epi32(z256[i], z256_im);
  z256[i] = _mm256_srai_epi32(z256_tmp_lo, 15);
  z256_im = _mm256_srai_epi32(z256_tmp_hi, 15);
  z256[i] = _mm256_packs_epi32(z256[i], z256_im);
  }

}

#else

 void componentwise_multiply_real_scalar(int16_t *x,int16_t *y,int16_t volatile *z,uint16_t N) {
	int i;

	for(i=0; i<N; i+=8){
		z[i] = FIX_MPY(x[i], y[i]);
		z[i+1] = FIX_MPY(x[i+1], y[i+1]);
		z[i+2] = FIX_MPY(x[i+2], y[i+2]);
		z[i+3] = FIX_MPY(x[i+3], y[i+3]);
		z[i+4] = FIX_MPY(x[i+4], y[i+4]);
		z[i+5] = FIX_MPY(x[i+5], y[i+5]);
		z[i+6] = FIX_MPY(x[i+6], y[i+6]);
		z[i+7] = FIX_MPY(x[i+7], y[i+7]);
	}

}

#ifdef _SSE4_
 void componentwise_multiply_real_sse4(int16_t *x,int16_t *y,int16_t volatile *z,uint16_t N) {

	__m128i *x128 = (__m128i *)x;
	__m128i *y128 = (__m128i *)y;
	__m128i *z128 = (__m128i *)z;
	int i;

	for(i=0; i<ceil(N/8.0); i+=8){
		z128[i] = _mm_mulhrs_epi16(x128[i], y128[i]);
		z128[i+1] = _mm_mulhrs_epi16(x128[i+1], y128[i+1]);
		z128[i+2] = _mm_mulhrs_epi16(x128[i+2], y128[i+2]);
		z128[i+3] = _mm_mulhrs_epi16(x128[i+3], y128[i+3]);
		z128[i+4] = _mm_mulhrs_epi16(x128[i+4], y128[i+4]);
		z128[i+5] = _mm_mulhrs_epi16(x128[i+5], y128[i+5]);
		z128[i+6] = _mm_mulhrs_epi16(x128[i+6], y128[i+6]);
		z128[i+7] = _mm_mulhrs_epi16(x128[i+7], y128[i+7]);
	}

}
#endif

#ifdef _AVX2_
 void componentwise_multiply_real_avx2(int16_t *x,int16_t *y,int16_t volatile *z, uint16_t N) {

	__m256i *x256 = (__m256i *)x;
	__m256i *y256 = (__m256i *)y;
	__m256i *z256 = (__m256i *)z;
	int i;
/*
  for(i=0; i<ceil(N/16.0); i++){
		z256[i] = _mm256_mulhrs_epi16(x256[i], y256[i]);
	}

*/
	for(i=0; i<ceil(N/16.0); i+=8){
		z256[i] = _mm256_mulhrs_epi16(x256[i], y256[i]);
		z256[i+1] = _mm256_mulhrs_epi16(x256[i+1], y256[i+1]);
		z256[i+2] = _mm256_mulhrs_epi16(x256[i+2], y256[i+2]);
		z256[i+3] = _mm256_mulhrs_epi16(x256[i+3], y256[i+3]);
		z256[i+4] = _mm256_mulhrs_epi16(x256[i+4], y256[i+4]);
		z256[i+5] = _mm256_mulhrs_epi16(x256[i+5], y256[i+5]);
		z256[i+6] = _mm256_mulhrs_epi16(x256[i+6], y256[i+6]);
		z256[i+7] = _mm256_mulhrs_epi16(x256[i+7], y256[i+7]);
	}

}
#endif

#ifdef _AVX512_
 void componentwise_multiply_real_avx512(int16_t *x,int16_t *y,int16_t *z, uint16_t N) {

	__m512i *x512 = (__m512i *)x;
	__m512i *y512 = (__m512i *)y;
	__m512i *z512 = (__m512i *)z;
	int i;


	for(i=0; i<ceil(N/32.0); i++){
		z512[i] = _mm512_mulhrs_epi16(x512[i], y512[i]);
	}

}
#endif

#endif

//debug print 128 bits in exadecimal
void print128_num(__m128i var)
{
    uint8_t *val = (uint8_t*) &var;
    printf("%.2x%.2x %.2x%.2x %.2x%.2x %.2x%.2x %.2x%.2x %.2x%.2x %.2x%.2x %.2x%.2x\n",
           val[15], val[14], val[13], val[12], val[11], val[10],
           val[9], val[8], val[7], val[6], val[5], val[4],
           val[3], val[2], val[1], val[0]);

}
