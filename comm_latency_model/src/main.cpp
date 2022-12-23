#include <chrono>
#include <iostream>
#include <cmath>
#include "OCL_Helpers.hpp"
extern  void scheduler(float ops[], bool & executeOnCPU, bool & executeOnFPGA, bool & lowConfidence) ;
extern  void train(float ops[], bool CPUwonFPGAlost) ;
extern cl::Kernel krnl_foo;
extern cl::Kernel krnl_bar;
extern cl::CommandQueue q;
extern cl::Context context;
using namespace std::chrono;
using namespace std;
void foo_KernelCount(int *X, int *res, float ops[]) {
   ops[4] = 10000;
   ops[5] = 5000;
}

#pragma clava kernel

#pragma clava data kernel : [{auto : "auto" }, {auto : "auto" }]

void fun_foo(int *X, int *res) {
   bool executeOnCPU;
   bool executeOnFPGA;
   bool measurePerf;
   std::chrono::high_resolution_clock::duration clava_timing_duration_0;
   std::chrono::high_resolution_clock::duration clava_timing_duration_1;
   float opsCount[16];
   foo_KernelCount(X, res, opsCount);
   scheduler(opsCount, executeOnCPU, executeOnFPGA, measurePerf);

   if(executeOnFPGA) {
      std::chrono::high_resolution_clock::time_point clava_timing_start_1;
      std::chrono::high_resolution_clock::time_point clava_timing_end_1;
      if(measurePerf) {
         clava_timing_start_1 = std::chrono::high_resolution_clock::now();
      }
      cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int *), X);
      krnl_foo.setArg(0, buffer_X);
      cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int *), res);
      krnl_foo.setArg(1, buffer_res);
      q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
      q.enqueueTask(krnl_foo);
      q.finish();
      q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
      q.finish();
      if(measurePerf) {
         clava_timing_end_1 = std::chrono::high_resolution_clock::now();
         clava_timing_duration_1 = clava_timing_end_1 - clava_timing_start_1;
      }
   }
   if(measurePerf) train(opsCount, clava_timing_duration_0 < clava_timing_duration_1);
}

int main_original() {
   int res = 0;
   int A[1000] = {0};
   auto start = high_resolution_clock::now();
   fun_foo(A, &res);
   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start);
   cout << "{" << 1000 << "} : " << duration.count() << endl;

   int E[100000] = {0};
   start = high_resolution_clock::now();
   fun_foo(E, &res);
   stop = high_resolution_clock::now();
   duration = duration_cast<microseconds>(stop - start);
   cout << "{" << 100000 << "} : " << duration.count() << endl;

   int I[1000000] = {0};
   start = high_resolution_clock::now();
   fun_foo(I, &res);
   stop = high_resolution_clock::now();
   duration = duration_cast<microseconds>(stop - start);
   cout << "{" << 1000000 << "} : " << duration.count() << endl;

   
   return 0;
}
