#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>

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

void convolve2d(int input_image[262144], int version, int output_image[262144]) {
#pragma HLS INLINE
   int i;
   int j;
   int c;
   int r;
   int normal_factor;
   int sum;
   int dead_rows;
   int dead_cols;
   int filter[9];
   if(version == 0) {
      filter[0] = 1;
      filter[1] = 2;
      filter[2] = 1;
      filter[3] = 2;
      filter[4] = 4;
      filter[5] = 2;
      filter[6] = 1;
      filter[7] = 2;
      filter[8] = 1;
   }
   if(version == 1) {
      filter[0] = 1;
      filter[1] = 0;
      filter[2] = -1;
      filter[3] = 2;
      filter[4] = 0;
      filter[5] = -2;
      filter[6] = 1;
      filter[7] = 0;
      filter[8] = -1;
   }
   if(version == 2) {
      filter[0] = 1;
      filter[1] = 2;
      filter[2] = 1;
      filter[3] = 0;
      filter[4] = 0;
      filter[5] = 0;
      filter[6] = -1;
      filter[7] = -2;
      filter[8] = -1;
   }
   dead_rows = 1;
   dead_cols = 1;
   normal_factor = 0;
   for(r = 0; r < 3; r++) {
      #pragma HLS unroll
      for(c = 0; c < 3; c++) {
         normal_factor += abs(filter[r * 3 + c]);
      }
   }
   if(normal_factor == 0) normal_factor = 1;
   for(r = 0; r < 510; r++) {
      for(c = 0; c < 510; c++) {
         #pragma HLS pipeline
         sum = 0;
         for(i = 0; i < 3; i++) {
            #pragma HLS unroll
            for(j = 0; j < 3; j++) {
               sum += input_image[(r + i) * 512 + (c + j)] * filter[i * 3 + j];
            }
         }
         output_image[(r + dead_rows) * 512 + (c + dead_cols)] = (sum / normal_factor);
      }
   }
}

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

void dataflow_function1(int image_rgb[786432], int image_gray[262144],int output[262144]) {
#pragma HLS ARRAY_PARTITION variable=output type=cyclic factor=1024
#pragma HLS dataflow
    rgbToGrayscale(image_rgb, image_gray);

    convolve2d(image_gray, 0, output);

    convolve2d(output, 1, image_gray);
}

void dataflow_function2(int image_gray[262144], int temp_buf[262144], int output[262144]) {
#pragma HLS ARRAY_PARTITION variable=output type=cyclic factor=1024
#pragma HLS dataflow
    convolve2d(output, 2, temp_buf);

    combthreshold(image_gray, temp_buf, output);
}

extern "C" {
void edge_detect_Kernel(int image_rgb[786432], int output[262144])  {
#pragma HLS ARRAY_PARTITION variable=output type=cyclic factor=1024
   int image_gray[262144] = {0};
   int temp_buf[262144] = {0};

   /*
   rgbToGrayscale(image_rgb, image_gray);
   convolve2d(image_gray, 0, output);
   convolve2d(output, 1, image_gray);
   convolve2d(output, 2, temp_buf);
   combthreshold(image_gray, temp_buf, output);
   */
   dataflow_function1(image_rgb, image_gray, output);

   dataflow_function2(image_gray, temp_buf, output);
}
}
