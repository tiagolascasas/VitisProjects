#include "OCL_Helpers.hpp"

cl::Context context;
cl::CommandQueue q;
cl::Program program;

extern int main_original();
cl::Kernel krnl_grayscale;
cl::Kernel krnl_combthreshold;

int main(int argc, char *argv[]) {
   static std::string const platformName = "Xilinx";
   OCLH::getConfig(argv[1], platformName, context, q, program);
   krnl_grayscale = OCLH::getKernel("rgbToGrayscale", program);
   krnl_combthreshold = OCLH::getKernel("combthreshold", program);
   return main_original();
}
