#include <stdint.h>

//Q15 multiply
// x and y are 16-bit integers (Q15)
int16_t FIX_MPY(int16_t x, int16_t y){

  return ((int16_t)(((int32_t)x * (int32_t)y)>>15));

}

//Saturated addition for Q15
int16_t SAT_ADD16(int16_t x,int16_t y) {

  if ((int32_t)x + (int32_t)y > 32767)
    return(32767);
  else if ((int32_t)x + (int32_t)y < -32767)
    return(-32768);
  else
    return(x+y);
}


