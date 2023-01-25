#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "config.h"
#include "util.h"
#include <cmath>
#include "OCL_Helpers.hpp"
#include <chrono>
using namespace std;
using namespace std::chrono;

extern cl::Kernel krnl_grayscale;
extern cl::Kernel krnl_combthreshold;
extern cl::CommandQueue q;
extern cl::Context context;

void convolve2d(int input_image[262144], int version, int output_image[262144]) {
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

void rgbToGrayscale(int image_rgb[786432], int output[262144]) {
  cl::Buffer buffer_image_rgb(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[786432]), image_rgb);
  krnl_grayscale.setArg(0, buffer_image_rgb);

  cl::Buffer buffer_output(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[262144]), output);
  krnl_grayscale.setArg(1, buffer_output);

  q.enqueueMigrateMemObjects({buffer_image_rgb, buffer_output}, 0 /* 0 means from host */);
  q.enqueueTask(krnl_grayscale);
  q.finish();
  q.enqueueMigrateMemObjects({buffer_image_rgb, buffer_output}, CL_MIGRATE_MEM_OBJECT_HOST);
  q.finish();
}

void combthreshold(int image_gray[262144], int temp_buf[262144], int output[262144]) {
  cl::Buffer buffer_image_gray(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[262144]), image_gray);
  krnl_combthreshold.setArg(0, buffer_image_gray);

  cl::Buffer buffer_temp_buf(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[262144]), temp_buf);
  krnl_combthreshold.setArg(1, buffer_temp_buf);

  cl::Buffer buffer_output(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[262144]), output);
  krnl_combthreshold.setArg(2, buffer_output);

  q.enqueueMigrateMemObjects({buffer_image_gray, buffer_temp_buf, buffer_output}, 0 /* 0 means from host */);
  q.enqueueTask(krnl_combthreshold);
  q.finish();
  q.enqueueMigrateMemObjects({buffer_image_gray, buffer_temp_buf, buffer_output}, CL_MIGRATE_MEM_OBJECT_HOST);
  q.finish();
}


void edge_detect(int image_rgb[786432], int output[262144])  {
   int image_gray[262144] = {0};
   rgbToGrayscale(image_rgb, image_gray);
   convolve2d(image_gray, 0, output);
   convolve2d(output, 1, image_gray);
   int temp_buf[262144] = {0};
   convolve2d(output, 2, temp_buf);
   combthreshold(image_gray, temp_buf, output);
}

int main_original() {
   int image_rgb[786432] = {
#include "img_512_512.dat"
   };
   int output[262144] = {0};

   auto start = high_resolution_clock::now();
   edge_detect(image_rgb, output);
   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start);
   cout << "Exec time: " << duration.count() << " microseconds" << endl;

   int actual = 0;
   int real = 2455650;
   for (int i = 0; i < 262144; i++) {
	   actual += output[i];
   }
   cout << "Checksum: real = " << real << ", actual = " << actual << (real == actual ? " (VERIFIED)" : " (ERROR)") << endl;
   return 0;
}
