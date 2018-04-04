// Include files for SSE4
#include <emmintrin.h>
#include <xmmintrin.h>
#include <stdint.h>
#include <tmmintrin.h>
// example SIMD macros, not necessary to be used, write your own

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

// routines to be written
void componentwise_multiply_real_scalar(int16_t *x,int16_t *y,int16_t *z,uint16_t N) {

}

// routines to be written
void componentwise_multiply_real_sse4(int16_t *x,int16_t *y,int16_t *z,uint16_t N) {

__m128i *x128 = (__m128i *)x;
__m128i *y128 = (__m128i *)y;
__m128i *z128 = (__m128i *)z;
 
}

int main() {
return 0;
}
