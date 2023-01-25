#include <chrono>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <string>
#include <fstream>
#include <thread>

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

unordered_map<int, int> umap;

void foo_N0(int res[1]) {
	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N0.setArg(0, buffer_res);

	q.enqueueTask(krnl_foo_N0);
	auto start = high_resolution_clock::now();

	q.enqueueMigrateMemObjects({buffer_res}, 0 /* 0 means from host */);
	q.finish();

#ifdef ROUNDTRIP
	q.enqueueMigrateMemObjects({buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	q.finish();
#endif

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	umap[N0] += duration.count();
}

void foo_N1(int X[N1], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N1]), X);
	krnl_foo_N1.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N1.setArg(1, buffer_res);

	q.enqueueTask(krnl_foo_N1);
	auto start = high_resolution_clock::now();

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.finish();

#ifdef ROUNDTRIP
	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	q.finish();
#endif

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	umap[N1] += duration.count();
}

void foo_N2(int X[N2], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N2]), X);
	krnl_foo_N2.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N2.setArg(1, buffer_res);

	q.enqueueTask(krnl_foo_N2);
	auto start = high_resolution_clock::now();

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.finish();

#ifdef ROUNDTRIP
	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	q.finish();
#endif

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	umap[N2] += duration.count();
}

void foo_N3(int X[N3], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N3]), X);
	krnl_foo_N3.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N3.setArg(1, buffer_res);

	q.enqueueTask(krnl_foo_N3);
	auto start = high_resolution_clock::now();

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.finish();

#ifdef ROUNDTRIP
	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	q.finish();
#endif

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	umap[N3] += duration.count();
}

void foo_N4(int X[N4], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N4]), X);
	krnl_foo_N4.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N4.setArg(1, buffer_res);

	q.enqueueTask(krnl_foo_N4);
	auto start = high_resolution_clock::now();

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.finish();

#ifdef ROUNDTRIP
	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	q.finish();
#endif

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	umap[N4] += duration.count();
}

void foo_N5(int X[N5], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N5]), X);
	krnl_foo_N5.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N5.setArg(1, buffer_res);

	q.enqueueTask(krnl_foo_N5);
	auto start = high_resolution_clock::now();

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.finish();

#ifdef ROUNDTRIP
	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	q.finish();
#endif

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	umap[N5] += duration.count();
}

void foo_N6(int X[N6], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N6]), X);
	krnl_foo_N6.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N6.setArg(1, buffer_res);

	q.enqueueTask(krnl_foo_N6);
	auto start = high_resolution_clock::now();

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.finish();

#ifdef ROUNDTRIP
	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	q.finish();
#endif

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	umap[N6] += duration.count();
}

void foo_N7(int X[N7], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N7]), X);
	krnl_foo_N7.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N7.setArg(1, buffer_res);

	q.enqueueTask(krnl_foo_N7);
	auto start = high_resolution_clock::now();

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.finish();

#ifdef ROUNDTRIP
	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	q.finish();
#endif

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	umap[N7] += duration.count();
}

void foo_N8(int X[N8], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N8]), X);
	krnl_foo_N8.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N8.setArg(1, buffer_res);

	q.enqueueTask(krnl_foo_N8);
	auto start = high_resolution_clock::now();

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.finish();

#ifdef ROUNDTRIP
	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	q.finish();
#endif

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	umap[N8] += duration.count();
}

void foo_N9(int X[N9], int res[1]) {
	cl::Buffer buffer_X(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[N9]), X);
	krnl_foo_N9.setArg(0, buffer_X);

	cl::Buffer buffer_res(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE, sizeof(int[1]), res);
	krnl_foo_N9.setArg(1, buffer_res);

	q.enqueueTask(krnl_foo_N9);
	auto start = high_resolution_clock::now();

	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, 0 /* 0 means from host */);
	q.finish();

#ifdef ROUNDTRIP
	q.enqueueMigrateMemObjects({buffer_X, buffer_res}, CL_MIGRATE_MEM_OBJECT_HOST);
	q.finish();
#endif

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	umap[N9] += duration.count();
}

int main_original() {
	string s = "size,time\n";

	for (int j = 0; j < RUNS; j++) {
		srand(time(0));
		int res[1] = {0};
		umap[N0] = 0;
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
			foo_N1(A, res);
			cout << "Finished N=" << N1 << ", iter=" << i << ", sample=" << j << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME));

			int *B = new int[N2];
			fill_n(B, N2, rand());
			foo_N2(B, res);
			cout << "Finished N=" << N2 << ", iter=" << i << ", sample=" << j << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME));

			int *C = new int[N3];
			fill_n(C, N3, rand());
			foo_N3(C, res);
			cout << "Finished N=" << N3 << ", iter=" << i << ", sample=" << j << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME));

			int *D = new int[N4];
			fill_n(D, N4, rand());
			foo_N4(D, res);
			cout << "Finished N=" << N4 << ", iter=" << i << ", sample=" << j << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME));

			int *E = new int[N5];
			fill_n(E, N5, rand());
			foo_N5(E, res);
			cout << "Finished N=" << N5 << ", iter=" << i << ", sample=" << j << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME));

			int *F = new int[N6];
			fill_n(F, N6, rand());
			foo_N6(F, res);
			cout << "Finished N=" << N6 << ", iter=" << i << ", sample=" << j << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME));

			int *G = new int[N7];
			fill_n(G, N7, rand());
			foo_N7(G, res);
			cout << "Finished N=" << N7 << ", iter=" << i << ", sample=" << j << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME));

			int *H = new int[N8];
			fill_n(H, N8, rand());
			foo_N8(H, res);
			cout << "Finished N=" << N8 << ", iter=" << i << ", sample=" << j << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME));

			int *I = new int[N9];
			fill_n(I, N9, rand());
			foo_N9(I, res);
			cout << "Finished N=" << N9 << ", iter=" << i << ", sample=" << j << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME));

			foo_N0(res);
			cout << "Finished N=" << 0 << ", iter=" << i << ", sample=" << j << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME));
		}

		stringstream ss;
		for (auto pair : umap) {
			ss << pair.first << ", " << (pair.second / ITER) - (umap[0] / ITER) << endl;
		 }

		s += ss.str();
	}

	ofstream csv;
	csv.open ("timing_res.csv");
	csv << s;
	csv.close();

	return 0;
}
