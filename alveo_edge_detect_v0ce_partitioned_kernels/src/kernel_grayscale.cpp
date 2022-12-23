#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>

extern "C" {
void rgbToGrayscale(int input_image[786432], int output_image[262144]) {
#pragma HLS INLINE
   for(int i = 0; i < 512; i++) {
      int jj = 0;
      for(int j = 0; j < 512; j++) {
         #pragma HLS pipeline
         int r = input_image[i * 512 * 3 + jj];
         int g = input_image[i * 512 * 3 + jj + 1];
         int b = input_image[i * 512 * 3 + jj + 2];
         jj += 3;
         float gray = 0.299 * r + 0.587 * g + 0.114 * b;
         output_image[i * 512 + j] = (int) floor(gray);
      }
   }
}
}
