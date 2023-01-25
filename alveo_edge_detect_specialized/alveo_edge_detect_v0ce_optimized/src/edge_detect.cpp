#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "config.h"
#include "util.h"
#include <cmath>
#include "OCL_Helpers.hpp"
#include <chrono>
#include <chrono>
using namespace std::chrono;

extern cl::Kernel krnl_edge_detect;
extern cl::CommandQueue q;
extern cl::Context context;

void edge_detect(int image_rgb[786432], int output[262144]) {
  cl::Buffer buffer_image_rgb(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[786432]), image_rgb);
  krnl_edge_detect.setArg(0, buffer_image_rgb);

  cl::Buffer buffer_output(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[262144]), output);
  krnl_edge_detect.setArg(1, buffer_output);

  q.enqueueMigrateMemObjects({buffer_image_rgb, buffer_output}, 0 /* 0 means from host */);
  q.enqueueTask(krnl_edge_detect);
  q.finish();
  q.enqueueMigrateMemObjects({buffer_image_rgb, buffer_output}, CL_MIGRATE_MEM_OBJECT_HOST);
  q.finish();
}

int main_original() {
   int image_rgb[786432] = {
#include "img_512_512.dat"
   };
   int output[262144] = {0};
   auto start = high_resolution_clock::now();
   edge_detect(image_rgb, output);
   // print image
   int actual = 0;
   int real = 2455650;
   for (int i = 0; i < 262144; i++) {
	   actual += output[i];
   }
   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start);
   std::cout << "Duration: " << duration.count() << std::endl;
   printf("Checksum: real = %d, actual = %d (%s)\n", actual, real, actual == real ? "VERIFIED" : "ERROR");
   return 0;
}
