#include "OCL_Helpers.hpp"
cl::Context context;
cl::CommandQueue q;
cl::Program program;
void scheduler(float ops[], bool & executeOnCPU, bool & executeOnFPGA, bool & lowConfidence) {
   executeOnCPU = false;
   executeOnFPGA = true;
   lowConfidence = false;
}

void train(float ops[], bool CPUwonFPGAlost) {
   
   return;
}

#pragma clava ocl_insert_globals

extern int main_original();
cl::Kernel krnl_foo;
// cl::Kernel krnl_scheduler;
int main(int argc, char *argv[]) {
   static std::string const platformName = "Xilinx";
   OCLH::getConfig(argv[1], platformName, context, q, program);
   #pragma clava ocl_insert_kernel_initializations
   krnl_foo = OCLH::getKernel("foo_Kernel", program);
   // krnl_scheduler = OCLH::getKernel("scheduler", program);
   
   return main_original();
}
