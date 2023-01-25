#include "OCL_Helpers.hpp"
cl::Context context;
cl::CommandQueue q;
cl::Program program;

#pragma clava ocl_insert_globals

extern int main_original();
cl::Kernel krnl_edge_detect;
// cl::Kernel krnl_scheduler;

int main(int argc, char *argv[]) {
	std::cout << argv[1] << std::endl;
   static std::string const platformName = "Xilinx";
   OCLH::getConfig(argv[1], platformName, context, q, program);
   #pragma clava ocl_insert_kernel_initializations
   krnl_edge_detect = OCLH::getKernel("edge_detect_Kernel", program);
   // krnl_scheduler = OCLH::getKernel("scheduler", program);
   
   return main_original();
}
