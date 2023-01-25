#include "OCL_Helpers.hpp"

cl::Context context;
cl::CommandQueue q;
cl::Program program;

extern int main_original();
cl::Kernel krnl_edge_detect;

int main(int argc, char *argv[]) {
   static std::string const platformName = "Xilinx";
   OCLH::getConfig(argv[1], platformName, context, q, program);
   krnl_edge_detect = OCLH::getKernel("edge_detect_Kernel", program);

   return main_original();
}
