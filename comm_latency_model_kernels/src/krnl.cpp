#include <cmath>

static void foo_KernelCode(int *X, int *res) {
   int c = 0;
   for(int i = 0; i < 1000000; i++) {
      c += pow(i * 2, 2);
   }
   *res = c;
}

extern "C" {
void foo_Kernel(int *X, int *res) {
   foo_KernelCode(X, res);
}
}
