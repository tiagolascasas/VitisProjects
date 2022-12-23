#include <chrono>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <string>
#include <fstream>

#include "OCL_Helpers.hpp"
#include "sizes.h"

using namespace std;
using namespace std::chrono;

extern cl::Kernel krnl_foo_N0;
extern cl::Kernel krnl_foo_N1;
extern cl::Kernel krnl_foo_N2;
extern cl::Kernel krnl_foo_N3;
extern cl::Kernel krnl_foo_N4;
extern cl::Kernel krnl_foo_N5;
extern cl::Kernel krnl_foo_N6;
extern cl::Kernel krnl_foo_N7;
extern cl::Kernel krnl_foo_N8;
extern cl::Kernel krnl_foo_N9;
extern cl::CommandQueue q;
extern cl::Context context;

void foo_N0(int res[1]) {
	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N0.setArg(0, buffer_res);

	q.enqueueMigrateMemObjects({buffer_res}, 0 /* 0 means from host */);
	q.enqueueTask(krnl_foo_N0);
	q.finish();
	//q.enqueueMigrateMemObjects({buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	//q.finish();
}

void foo_N1(int X[N1], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N1]), X);
	krnl_foo_N1.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N1.setArg(1, buffer_res);

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.enqueueTask(krnl_foo_N1);
	q.finish();
	//q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	//q.finish();
}

void foo_N2(int X[N2], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N2]), X);
	krnl_foo_N2.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N2.setArg(1, buffer_res);

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.enqueueTask(krnl_foo_N2);
	q.finish();
	//q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	//q.finish();
}

void foo_N3(int X[N3], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N3]), X);
	krnl_foo_N3.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N3.setArg(1, buffer_res);

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.enqueueTask(krnl_foo_N3);
	q.finish();
	//q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	//q.finish();
}

void foo_N4(int X[N4], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N4]), X);
	krnl_foo_N4.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N4.setArg(1, buffer_res);

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.enqueueTask(krnl_foo_N4);
	q.finish();
	//q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	//q.finish();
}

void foo_N5(int X[N5], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N5]), X);
	krnl_foo_N5.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N5.setArg(1, buffer_res);

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.enqueueTask(krnl_foo_N5);
	q.finish();
	//q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	//q.finish();
}

void foo_N6(int X[N6], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N6]), X);
	krnl_foo_N6.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N6.setArg(1, buffer_res);

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.enqueueTask(krnl_foo_N6);
	q.finish();
	//q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	//q.finish();
}

void foo_N7(int X[N7], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N7]), X);
	krnl_foo_N7.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N7.setArg(1, buffer_res);

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.enqueueTask(krnl_foo_N7);
	q.finish();
	//q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	//q.finish();
}

void foo_N8(int X[N8], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N8]), X);
	krnl_foo_N8.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N8.setArg(1, buffer_res);

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.enqueueTask(krnl_foo_N8);
	q.finish();
	//q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	//q.finish();
}

void foo_N9(int X[N9], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N9]), X);
	krnl_foo_N9.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N9.setArg(1, buffer_res);

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.enqueueTask(krnl_foo_N9);
	q.finish();
	//q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	//q.finish();
}

int main_original() {
	string s = "size,time\n";

	for (int j = 0; j < 10; j++) {
		srand(time(0));
		int res[1] = {0};
		unordered_map<int, int> umap;
		umap[0] = 0;
		umap[N1] = 0;
		umap[N2] = 0;
		umap[N3] = 0;
		umap[N4] = 0;
		umap[N5] = 0;
		umap[N6] = 0;
		umap[N7] = 0;
		umap[N8] = 0;
		umap[N9] = 0;

		for (int i = 0; i < ITER; i++) {
			int *A = new int[N1];
			fill_n(A, N1, rand());
			auto start = high_resolution_clock::now();
			foo_N1(A, res);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			umap[N1] += duration.count();

			int *B = new int[N2];
			fill_n(B, N2, rand());
			start = high_resolution_clock::now();
			foo_N2(B, res);
			stop = high_resolution_clock::now();
			duration = duration_cast<microseconds>(stop - start);
			umap[N2] += duration.count();

			int *C = new int[N3];
			fill_n(C, N3, rand());
			start = high_resolution_clock::now();
			foo_N3(C, res);
			stop = high_resolution_clock::now();
			duration = duration_cast<microseconds>(stop - start);
			umap[N3] += duration.count();

			int *D = new int[N4];
			fill_n(D, N4, rand());
			start = high_resolution_clock::now();
			foo_N4(D, res);
			stop = high_resolution_clock::now();
			duration = duration_cast<microseconds>(stop - start);
			umap[N4] += duration.count();

			int *E = new int[N5];
			fill_n(E, N5, rand());
			start = high_resolution_clock::now();
			foo_N5(E, res);
			stop = high_resolution_clock::now();
			duration = duration_cast<microseconds>(stop - start);
			umap[N5] += duration.count();

			int *F = new int[N6];
			fill_n(F, N6, rand());
			start = high_resolution_clock::now();
			foo_N6(F, res);
			stop = high_resolution_clock::now();
			duration = duration_cast<microseconds>(stop - start);
			umap[N6] += duration.count();

			int *G = new int[N7];
			fill_n(G, N7, rand());
			start = high_resolution_clock::now();
			foo_N7(G, res);
			stop = high_resolution_clock::now();
			duration = duration_cast<microseconds>(stop - start);
			umap[N7] += duration.count();

			int *H = new int[N8];
			fill_n(H, N8, rand());
			start = high_resolution_clock::now();
			foo_N8(H, res);
			stop = high_resolution_clock::now();
			duration = duration_cast<microseconds>(stop - start);
			umap[N8] += duration.count();

			int *I = new int[N9];
			fill_n(I, N9, rand());
			start = high_resolution_clock::now();
			foo_N9(I, res);
			stop = high_resolution_clock::now();
			duration = duration_cast<microseconds>(stop - start);
			umap[N9] += duration.count();

			start = high_resolution_clock::now();
			foo_N0(res);
			stop = high_resolution_clock::now();
			duration = duration_cast<microseconds>(stop - start);
			umap[0] += duration.count();
		}

		stringstream ss;
		for (auto pair : umap) {
			ss << pair.first << ", " << (pair.second / ITER) - (umap[0] / ITER) << endl;
		 }

		s += ss.str();
	}

	ofstream csv;
	csv.open ("res.csv");
	csv << s;
	csv.close();

	return 0;
}
