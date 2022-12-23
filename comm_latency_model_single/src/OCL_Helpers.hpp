#ifndef __OCL_Helpers__
#define __OCL_Helpers__

//#include "xcl2.hpp"

#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1
#define CL_HPP_ENABLE_EXCEPTIONS

#include "CL/cl2.hpp"

#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#ifdef OCL_CHECK
#undef OCL_CHECK
#endif

#ifdef OCL_DEBUG_INFO
#define OCL_CHECK(errorVar, stmt)                                              \
    stmt;                                                                      \
    if (errorVar != CL_SUCCESS) {                                              \
        std::cout << __FILE__ << ":" << __LINE__ << "Error calling " << #stmt  \
                  << ", error code is " << errorVar << std::endl;              \
        exit(EXIT_FAILURE);                                                    \
    }
#else
#define OCL_CHECK(errorVar, stmt) stmt;
#endif

namespace OCLH {

std::vector<char> readBinaryFile(const char *fileName);

std::vector<char> readBinaryFile(const std::string &fileName);

cl_int getConfigFromDeviceList(cl::Device &device, cl::Program::Binaries &bins,
                               cl::Context &context, cl::CommandQueue &q,
                               cl::Program &program);

void getConfig(const char *file, const std::string platformName,
               cl::Context &context, cl::CommandQueue &q, cl::Program &program);

cl::Kernel &getKernel(const char *kernelName, cl::Program &program);
cl::Kernel &getKernel(const std::string kernelName, cl::Program &program);

} // namespace OCLH

#endif
