#include <iostream>

// oneAPI headers
#include <sycl.hpp>
#include <sycl/ext/intel/fpga_extensions.hpp>

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
  bool passed = false;

  try {
#if FPGA_SIMULATOR
    std::cout << "using FPGA Simulator." << std::endl;
    sycl::queue q(sycl::ext::intel::fpga_simulator_selector{});
#elif FPGA_HARDWARE
    std::cout << "using FPGA Hardware." << std::endl;
    sycl::queue q(sycl::ext::intel::fpga_selector{});
#else  // #if FPGA_EMULATOR
    std::cout << "using FPGA Emulator." << std::endl;
    sycl::queue q(sycl::ext::intel::fpga_emulator_selector{});
#endif

    int count = VECT_SIZE;  // pass array size by value

    // declare arrays and fill them
    int *A = new int[count];
    int *B = new int[count];
    int *C = new int[count];
    for (int i = 0; i < count; i++) {
      A[i] = i;
      B[i] = (count - i);
    }

    // Copy to device memory so kernel can see them
    int *A_device = sycl::malloc_device<int>(count, q);
    q.memcpy(A_device, A, count * sizeof(int)).wait();
    int *B_device = sycl::malloc_device<int>(count, q);
    q.memcpy(B_device, B, count * sizeof(int)).wait();
    int *C_device = sycl::malloc_device<int>(count, q);

    std::cout << "A_device = " << A_device << std::endl;
    std::cout << "B_device = " << B_device << std::endl;
    std::cout << "C_device = " << C_device << std::endl;

    std::cout << "add two vectors of size " << count << std::endl;

    q.single_task<SimpleVAdd>(
         SimpleVAddKernel{A_device, B_device, C_device, count})
        .wait();

    // Copy from device memory 
    q.memcpy(C, C_device, count * sizeof(int));

    sycl::free(A, q);
    sycl::free(B, q);
    sycl::free(C, q);

    // verify that VC is correct
    passed = true;
    for (int i = 0; i < count; i++) {
      int expected = A[i] + B[i];
      if (C[i] != expected) {
        std::cout << "idx=" << i << ": result " << C[i] << ", expected ("
                  << expected << ") A=" << A[i] << " + B=" << B[i] << std::endl;
        passed = false;
      }
    }

    std::cout << (passed ? "PASSED" : "FAILED") << std::endl;

    delete [] A;
    delete [] B;
    delete [] C;

  } catch (sycl::exception const &e) {
    // Catches exceptions in the host code.
    std::cerr << "Caught a SYCL host exception:\n" << e.what() << "\n";

    // Most likely the runtime couldn't find FPGA hardware!
    if (e.code().value() == CL_DEVICE_NOT_FOUND) {
      std::cerr << "If you are targeting an FPGA, please ensure that your "
                   "system has a correctly configured FPGA board.\n";
      std::cerr << "Run sys_check in the oneAPI root directory to verify.\n";
      std::cerr << "If you are targeting the FPGA emulator, compile with "
                   "-DFPGA_EMULATOR.\n";
    }
    std::terminate();
  }

  return passed ? EXIT_SUCCESS : EXIT_FAILURE;
}