#include "OCL_Helpers.hpp"

std::vector<char> OCLH::readBinaryFile(const char *fileName) {
    std::cout << "Loading '" << fileName << "'..." << std::endl;

    std::ifstream xclbinFile(fileName, std::ifstream::binary);

    xclbinFile.seekg(0, xclbinFile.end);
    size_t size = xclbinFile.tellg();
    xclbinFile.seekg(0, xclbinFile.beg);

    std::vector<char> buffer(size);

    xclbinFile.read((char *)buffer.data(), size);

    return buffer;
}

std::vector<char> OCLH::readBinaryFile(const std::string &fileName) {
    return readBinaryFile(fileName.c_str());
}

cl_int OCLH::getConfigFromDeviceList(cl::Device &device,
                                     cl::Program::Binaries &bins,
                                     cl::Context &context, cl::CommandQueue &q,
                                     cl::Program &program) {
    cl_int err;

    OCL_CHECK(err,
              context = cl::Context(device, nullptr, nullptr, nullptr, &err));

    OCL_CHECK(err, q = cl::CommandQueue(context, device,
                                        CL_QUEUE_PROFILING_ENABLE, &err));

    program = cl::Program(context, {device}, bins, nullptr, &err);

    return err;
}

void OCLH::getConfig(const char *file, const std::string platformName,
                     cl::Context &context, cl::CommandQueue &q,
                     cl::Program &program) {

    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    std::vector<cl::Device> devices;
    cl::Device device;

    cl_int err;

    auto b = readBinaryFile(file);
    cl::Program::Binaries bins{{b.data(), b.size()}};

    for (auto &platform : platforms) {

        std::string currentPlatformName = platform.getInfo<CL_PLATFORM_NAME>();

        if (currentPlatformName == platformName) {
            devices.clear();
            platform.getDevices(CL_DEVICE_TYPE_ACCELERATOR, &devices);

            for (auto &device : devices) {

                std::cout << "Using device \""
                          << device.getInfo<CL_DEVICE_NAME>() << "\" - ";

                err =
                    getConfigFromDeviceList(device, bins, context, q, program);

                if (err != CL_SUCCESS) {
                    std::cout << "FAILED" << std::endl;
                } else {
                    std::cout << "SUCCESS" << std::endl;
                    return;
                }
            }
        }
    }

    exit(EXIT_FAILURE);
}

cl::Kernel &OCLH::getKernel(const char *kernelName, cl::Program &program) {
    cl_int err;
    OCL_CHECK(err,
              cl::Kernel &kernel = *new cl::Kernel(program, kernelName, &err));

    return kernel;
}

cl::Kernel &OCLH::getKernel(const std::string kernelName,
                            cl::Program &program) {
    return getKernel(kernelName.c_str(), program);
}
