// Include files for SSE4
#include "emmintrin.h"
#include "xmmintrin.h"
#include <stdint.h>

// example SIMD macros, not necessary to be used, write your own

inline void cmult(__m128i a,__m128i b, __m128i *re32, __m128i *im32) {

  mmtmpb    = _mm_sign_epi16(b,*(__m128i*)reflip);
  *re32     = _mm_madd_epi16(a,mmtmpb);
  mmtmpb    = _mm_shufflelo_epi16(b,_MM_SHUFFLE(2,3,0,1));
  mmtmpb    = _mm_shufflehi_epi16(mmtmpb,_MM_SHUFFLE(2,3,0,1));
  *im32  = _mm_madd_epi16(a,mmtmpb);

}

__m128i cpack_tmp1,cpack_tmp2;
inline __m128i cpack(__m128i xre,__m128i xim) {

  cpack_tmp1 = _mm_unpacklo_epi32(xre,xim);
  cpack_tmp1 = _mm_srai_epi32(cpack_tmp1,15);
  cpack_tmp2 = _mm_unpackhi_epi32(xre,xim);
  cpack_tmp2 = _mm_srai_epi32(cpack_tmp2,15);
  return(_mm_packs_epi32(cpack_tmp1,cpack_tmp2));

}

// routines to be written
void componentwise_multiply_real_scalar(int16_t *x,int16_t *y,int16_t *z,uint16_t N) {

}
_
// routines to be written
void componentwise_multiply_real_sse4(int16_t *x,int16_t *y,int16_t *z,uint16_t N) {

__m128i *x128 = (__m128i *)x;
__m128i *y128 = (__m128i *)y;
__m128i *z128 = (__m128i *)z;
 
}

main() {

}
