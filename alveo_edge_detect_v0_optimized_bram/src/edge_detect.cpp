#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "config.h"
#include "util.h"
#include <cmath>
#include "OCL_Helpers.hpp"
#include <chrono>
using namespace std::chrono;

extern cl::Kernel krnl_edge_detect;
extern cl::CommandQueue q;
extern cl::Context context;

#pragma clava kernel

#pragma clava data kernel : [{                                                 \
auto : "auto" },                                                           \
{auto : "auto" }, {auto : "auto" }, {auto : "auto" },                    \
{auto : "auto" }, {auto : "auto" }]

void edge_detect() {
	q.enqueueTask(krnl_edge_detect);
	q.finish();
}

int main_original() {
	auto start = high_resolution_clock::now();
	edge_detect();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Duration: " << duration.count() << std::endl;
	// not possible to print image, no data returns from kernel...
	/*
	int actual = 0;
	int real = 2455650;
	for (int i = 0; i < 262144; i++) {
		actual += output[i];
	}
	printf("Checksum: real = %d, actual = %d (%s)\n", actual, real,
			actual == real ? "VERIFIED" : "ERROR");
			*/

	return 0;
}
