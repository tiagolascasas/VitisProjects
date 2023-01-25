#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>

extern "C" {
void combthreshold(int image_gray[262144], int temp_buf[262144], int output[262144]) {
#pragma HLS INLINE
   int j;
   int i;
   int temp1;
   int temp2;
   int temp3;
   for(i = 0; i < 512; i++) {
      for(j = 0; j < 512; ++j) {
         #pragma HLS pipeline
         temp1 = abs(image_gray[i * 512 + j]);
         temp2 = abs(temp_buf[i * 512 + j]);
         temp3 = (temp1 > temp2) ? temp1 : temp2;
         output[i * 512 + j] = (temp3 > 50) ? 255 : 0;
      }
   }
}
}
