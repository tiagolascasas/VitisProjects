#include <cmath>
#include "kernel.h"

extern "C" {
void kernel_foo_N8(int X[N8], int res[1])
{
	//input independent busy work
    int c = 0;
    for (int i = 0; i < 5000; i++)
        c += pow(i * 2, 2);
    res[0] = c;
}
}
