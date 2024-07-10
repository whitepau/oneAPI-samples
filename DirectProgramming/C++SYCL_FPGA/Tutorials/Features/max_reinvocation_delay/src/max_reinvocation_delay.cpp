#include <iostream>
#include <sycl/ext/intel/fpga_extensions.hpp>
#include <sycl/sycl.hpp>

#include "exception_handler.hpp"
#include "sequence_kernel_constrained.hpp"
#include "sequence_kernel_unconstrained.hpp"

constexpr int kFactors = 5;

template <typename DataPipe>
bool VerifyFunctionalCorrectness(sycl::queue q, int first_term,
                                 int sequence_length) {
  bool passed = true;
  for (int factor = 1; factor <= kFactors; factor++) {
    std::cout << "Review arithmetic sequence with factor = " << factor
              << std::endl;
    for (int i = 0; i < sequence_length; i++) {
      int val_device = DataPipe::read(q);
      int val_host = first_term + i * factor;
      passed &= (val_device == val_host);
      if (val_device != val_host) {
        std::cout << "Error: expected " << val_host << ", got " << val_device
                  << std::endl;
      }
    }
  }

  return passed;
}

int main() {
  try {
#if FPGA_SIMULATOR
    auto selector = sycl::ext::intel::fpga_simulator_selector_v;
#elif FPGA_HARDWARE
    auto selector = sycl::ext::intel::fpga_selector_v;
#else  // #if FPGA_EMULATOR
    auto selector = sycl::ext::intel::fpga_emulator_selector_v;
#endif
    sycl::queue q(selector, fpga_tools::exception_handler);
    auto device = q.get_device();
    std::cout << "Running on device: "
              << device.get_info<sycl::info::device::name>().c_str()
              << std::endl;

    int first_term = 0;
    int sequence_length = 10;

    q.single_task<SequenceConstrained>(
        SequenceKernelConstrained<kFactors>{first_term, sequence_length});
    q.single_task<SequenceUnconstrained>(
        SequenceKernelUnconstrained<kFactors>{first_term, sequence_length});

    bool passed = true;

    std::cout << "Test constrained kernel:" << std::endl;
    passed &= VerifyFunctionalCorrectness<PipeResultsConstrained>(
        q, first_term, sequence_length);

    std::cout << "Test unconstrained kernel:" << std::endl;
    passed &= VerifyFunctionalCorrectness<PipeResultsUnconstrained>(
        q, first_term, sequence_length);

    std::cout << (passed ? "PASSED" : "FAILED") << std::endl;
    return passed ? EXIT_SUCCESS : EXIT_FAILURE;

  } catch (sycl::exception const &e) {
    std::cerr << "Caught a synchronous SYCL exception: " << e.what()
              << std::endl;
    std::cerr << "   If you are targeting an FPGA hardware, "
                 "ensure that your system is plugged to an FPGA board that is "
                 "set up correctly"
              << std::endl;
    std::cerr << "   If you are targeting the FPGA emulator, compile with "
                 "-DFPGA_EMULATOR"
              << std::endl;
    std::terminate();
  }
}