#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "config.h"
#include "util.h"
#include <cmath>
#include "OCL_Helpers.hpp"
#include <chrono>
using namespace std::chrono;
extern  void scheduler(float ops[], bool & executeOnCPU, bool & executeOnFPGA, bool & lowConfidence) ;
extern  void train(float ops[], bool CPUwonFPGAlost) ;
extern cl::Kernel krnl_edge_detect;
extern cl::CommandQueue q;
extern cl::Context context;


void edge_detect_KernelCount(int image_rgb[786432], int image_gray[262144], int temp_buf[262144], int filter[9], int output[262144], float ops[]) {
   ops[4] = 19534612;
   ops[5] = 9904249;
   ops[6] = 260102;
   ops[12] = 524288;
   ops[13] = 786432;
}

#pragma clava kernel

#pragma clava data kernel : [{                                                 \
auto : "auto" },                                                           \
{auto : "auto" }, {auto : "auto" }, {auto : "auto" },                    \
{auto : "auto" }, {auto : "auto" }]

void edge_detect(int image_rgb[786432], int image_gray[262144], int temp_buf[262144], int filter[9], int output[262144]) {
   bool executeOnCPU;
   bool executeOnFPGA;
   bool measurePerf;
   std::chrono::high_resolution_clock::duration clava_timing_duration_0;
   std::chrono::high_resolution_clock::duration clava_timing_duration_1;
   float opsCount[16];
   edge_detect_KernelCount(image_rgb, image_gray, temp_buf, filter, output, opsCount);
   scheduler(opsCount, executeOnCPU, executeOnFPGA, measurePerf);

   if(executeOnFPGA) {
      std::chrono::high_resolution_clock::time_point clava_timing_start_1;
      std::chrono::high_resolution_clock::time_point clava_timing_end_1;
      if(measurePerf) {
         clava_timing_start_1 = std::chrono::high_resolution_clock::now();
      }
      cl::Buffer buffer_image_rgb(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[786432]), image_rgb);
      krnl_edge_detect.setArg(0, buffer_image_rgb);
      cl::Buffer buffer_image_gray(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[262144]), image_gray);
      krnl_edge_detect.setArg(1, buffer_image_gray);
      cl::Buffer buffer_temp_buf(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[262144]), temp_buf);
      krnl_edge_detect.setArg(2, buffer_temp_buf);
      cl::Buffer buffer_filter(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[9]), filter);
      krnl_edge_detect.setArg(3, buffer_filter);
      cl::Buffer buffer_output(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[262144]), output);
      krnl_edge_detect.setArg(4, buffer_output);
      q.enqueueMigrateMemObjects({buffer_image_rgb, buffer_image_gray, buffer_temp_buf, buffer_filter, buffer_output}, 0 /* 0 means from host */);
      q.enqueueTask(krnl_edge_detect);
      q.finish();
      q.enqueueMigrateMemObjects({buffer_image_rgb, buffer_image_gray, buffer_temp_buf, buffer_filter, buffer_output}, CL_MIGRATE_MEM_OBJECT_HOST);
      q.finish();
      if(measurePerf) {
         clava_timing_end_1 = std::chrono::high_resolution_clock::now();
         clava_timing_duration_1 = clava_timing_end_1 - clava_timing_start_1;
      }
   }
   if(measurePerf) train(opsCount, clava_timing_duration_0 < clava_timing_duration_1);
}

int main_original() {
   int image_rgb[786432] = {
#include "img_512_512.dat"
   };
   int image_gray[262144] = {0};
   int temp_buf[262144] = {0};
   int filter[9] = {0};
   int output[262144] = {0};
   auto start = high_resolution_clock::now();
   edge_detect(image_rgb, image_gray, temp_buf, filter, output);
   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start);
   std::cout << "Duration: " << duration.count() << std::endl;
   // print image
   int actual = 0;
   int real = 2455650;
   for (int i = 0; i < 262144; i++) {
	   actual += output[i];
   }
   printf("Checksum: real = %d, actual = %d (%s)\n", actual, real, actual == real ? "VERIFIED" : "ERROR");
   
   return 0;
}
