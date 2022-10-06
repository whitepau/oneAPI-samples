#include <iostream>

// oneAPI headers
#include <CL/sycl.hpp>
#include <sycl/ext/intel/fpga_extensions.hpp>

using namespace sycl;

// Forward declare the kernel name in the global scope. This is an FPGA best
// practice that reduces name mangling in the optimization reports.
class SimpleVAdd;

class SimpleVAddKernel {
 public:
  int *A_in;
  int *B_in;
  int *C_out;
  int len;

  void operator()() const {
    for (int idx = 0; idx < len; idx++) {
      int a_val = A_in[idx];
      int b_val = B_in[idx];
      int sum = a_val + b_val;
      C_out[idx] = sum;
    }
  }
};

#define VECT_SIZE 256

int main() {
#if FPGA_SIMULATOR
  std::cout << "using FPGA Simulator." << std::endl;
  return sycl::ext::intel::fpga_simulator_selector{};
#elif FPGA_HARDWARE
  std::cout << "using FPGA Hardware." << std::endl;
  return sycl::ext::intel::fpga_selector{};
#else  // #if FPGA_EMULATOR
  std::cout << "using FPGA Emulator." << std::endl;
  return sycl::ext::intel::fpga_emulator_selector{};
#endif

  int count = VECT_SIZE;  // pass array size by value

  // declare arrays and fill them
  // allocate in shared memory so the kernel can see them
  int *A = malloc_shared<int>(count, q);
  int *B = malloc_shared<int>(count, q);
  int *C = malloc_shared<int>(count, q);
  for (int i = 0; i < count; i++) {
    A[i] = i;
    B[i] = (count - i);
  }

  std::cout << "add two vectors of size " << count << std::endl;

  q.single_task<SimpleVAdd>(SimpleVAddKernel{A, B, C, count}).wait();

  // verify that VC is correct
  bool passed = true;
  for (int i = 0; i < count; i++) {
    int expected = A[i] + B[i];
    if (C[i] != expected) {
      std::cout << "idx=" << i << ": result " << C[i] << ", expected ("
                << expected << ") A=" << A[i] << " + B=" << B[i] << std::endl;
      passed = false;
    }
  }

  std::cout << (passed ? "PASSED" : "FAILED") << std::endl;

  free(A, q);
  free(B, q);
  free(C, q);

  return passed ? EXIT_SUCCESS : EXIT_FAILURE;
}