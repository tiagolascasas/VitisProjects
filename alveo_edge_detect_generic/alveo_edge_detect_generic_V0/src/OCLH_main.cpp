#include <iostream>
#include "OCL_Helpers.hpp"
using namespace std;

cl::Context context;
cl::CommandQueue q;
cl::Program program;

extern int main_original();
cl::Kernel krnl_edge_detect;

int main(int argc, char *argv[]) {
	std::cout << argv[1] << std::endl;
    static std::string const platformName = "Xilinx";
    OCLH::getConfig(argv[1], platformName, context, q, program);
    krnl_edge_detect = OCLH::getKernel("edge_detect", program);

    return main_original();
}
