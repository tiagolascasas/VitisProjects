#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cmath>
#include <chrono>

#include "OCL_Helpers.hpp"
#include "config.h"
#include "util.h"

using namespace std;
using namespace std::chrono;
extern cl::Kernel krnl_edge_detect;
extern cl::CommandQueue q;
extern cl::Context context;

void edge_detect(int image_rgb[H * W * 3], int output[H * W], int width, int height) {

	cl::Buffer buffer_image_rgb(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[H * W * 3]), image_rgb);
	krnl_edge_detect.setArg(0, buffer_image_rgb);

	cl::Buffer buffer_output(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[H * W]), output);
	krnl_edge_detect.setArg(1, buffer_output);

	krnl_edge_detect.setArg(2, width);

	krnl_edge_detect.setArg(3, height);

	q.enqueueMigrateMemObjects( { buffer_image_rgb, buffer_output }, 0 /* 0 means from host */);
	q.enqueueTask(krnl_edge_detect);
	q.finish();

	q.enqueueMigrateMemObjects( { buffer_output }, CL_MIGRATE_MEM_OBJECT_HOST);
	q.finish();
}

int image_rgb[H * W * 3] = {
#include IMAGE
		};
int* output = new int[H * W];

int main_original() {
	auto start = high_resolution_clock::now();
#if ITER > 0
	int i;
	for (i = 0; i < ITER; i++)
	{
#endif
	edge_detect(image_rgb, output, W, H);
#if ITER > 0
}
#endif
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Duration: " << duration.count() << std::endl;

    int actual = 0;
    int real = CHECKSUM;
    for (int i = 0; i < H * W; i++)
    {
        actual += output[i];
    }
    cout << "Edge detect for " << W << "x" << H << " image finished" << endl;
    cout << "Checksum: expected = " << real << ", actual = " << actual << (real == actual ? " (VERIFIED)" : " (ERROR)") << endl;

	return 0;
}
