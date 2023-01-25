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

void edge_detect(int image_rgb[H * W * 3], int image_gray[H * W],
		int temp_buf[H * W], int filter[K * K], int output[H * W], int width, int height) {

	cl::Buffer buffer_image_rgb(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[H * W * 3]), image_rgb);
	krnl_edge_detect.setArg(0, buffer_image_rgb);

	cl::Buffer buffer_image_gray(context,CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[H * W]), image_gray);
	krnl_edge_detect.setArg(1, buffer_image_gray);

	cl::Buffer buffer_temp_buf(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[H * W]), temp_buf);
	krnl_edge_detect.setArg(2, buffer_temp_buf);

	cl::Buffer buffer_filter(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[K * K]), filter);
	krnl_edge_detect.setArg(3, buffer_filter);

	cl::Buffer buffer_output(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[H * W]), output);
	krnl_edge_detect.setArg(4, buffer_output);

	krnl_edge_detect.setArg(5, width);

	krnl_edge_detect.setArg(6, height);

	q.enqueueMigrateMemObjects( { buffer_image_rgb, buffer_image_gray, buffer_temp_buf, buffer_filter, buffer_output }, 0 /* 0 means from host */);
	q.enqueueTask(krnl_edge_detect);
	q.finish();

	q.enqueueMigrateMemObjects( { buffer_image_rgb, buffer_image_gray, buffer_temp_buf, buffer_filter, buffer_output }, CL_MIGRATE_MEM_OBJECT_HOST);
	q.finish();
}

int main_original() {
	//int image_rgb[H * W * 3] = {
//#include IMAGE
//			};
	int* image_rgb = new int[H * W * 3];
#ifdef MAIN_ALL
	int* image_gray = new int[H * W];// = { 0 };
	int* temp_buf = new int[H * W];// = { 0 };
	int* filter = new int[K * K];// = { 0 };
#endif
	int* output = new int[H * W];// = { 0 };

#ifdef OUTS
	output_dsp_rgb(image_rgb, "input.dat");
#endif

	auto start = high_resolution_clock::now();
#if ITER > 0
	int i;
	for (i = 0; i < ITER; i++)
	{
#endif
	edge_detect(image_rgb,
#ifdef MAIN_ALL
			image_gray, temp_buf, filter,
#endif
			output, W, H);
#if ITER > 0
}
#endif
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Duration: " << duration.count() << std::endl;

	int actual = 0;
	int real = CHECKSUM;
	for (int i = 0; i < 262144; i++) {
		actual += output[i];
	}
	cout << "Checksum: expected = " << real << ", actual = " << actual
			<< (real == actual ? " (VERIFIED)" : " (ERROR)") << endl;

	return 0;
}
