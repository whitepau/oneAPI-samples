//  Copyright (c) 2023 Intel Corporation
//  SPDX-License-Identifier: MIT

#include <stdlib.h>

#include <iostream>

// oneAPI headers
#include <sycl/ext/intel/fpga_extensions.hpp>
#include <sycl/ext/intel/prototype/host_pipes.hpp>
#include <sycl/sycl.hpp>

#include "exception_handler.hpp"

// use host pipes to write into addresses in the CSR
class OutputPipeID;
using OutputPipe = sycl::ext::intel::prototype::pipe<
    OutputPipeID, int, 1,
    // choose defaults for these 4:
    0, 1, true, false,
    // store the most recently processed index to the CSR
    sycl::ext::intel::prototype::internal::protocol_name::AVALON_MM>;

// Forward declare the kernel name in the global scope. This is an FPGA best
// practice that reduces name mangling in the optimization reports.
class AdderID;

class Adder {
 public:
  int a;
  int b;

  void operator()() const {
    int sum = a + b;

    OutputPipe::write(sum);
  }
};

int main() {
  bool passed = false;

  try {
// This design is tested with 2023.0, but also accounts for a syntax change in
// 2023.1
#if __INTEL_CLANG_COMPILER >= 20230100
#if FPGA_SIMULATOR
    auto selector = sycl::ext::intel::fpga_simulator_selector_v;
#elif FPGA_HARDWARE
    auto selector = sycl::ext::intel::fpga_selector_v;
#else  // #if FPGA_EMULATOR
    auto selector = sycl::ext::intel::fpga_emulator_selector_v;
#endif
#elif __INTEL_CLANG_COMPILER >= 20230000
#if FPGA_SIMULATOR
    auto selector = sycl::ext::intel::fpga_simulator_selector{};
#elif FPGA_HARDWARE
    auto selector = sycl::ext::intel::fpga_selector{};
#else  // #if FPGA_EMULATOR
    auto selector = sycl::ext::intel::fpga_emulator_selector{};
#endif
#else
    assert(false) && "this design requires oneAPI 2023.0 or 2023.1!"
#endif

    sycl::queue q(selector, fpga_tools::exception_handler,
                  sycl::property::queue::enable_profiling{});

    int a = 3;
    int b = 76;

    int expectedSum = a + b;

    std::cout << "add two integers using CSR for input." << std::endl;

    // no need to wait() since the pipe read will block until `Adder` has some
    // output.
    q.single_task<AdderID>(Adder{a, b});

    // verify that outputs are correct
    passed = true;

    std::cout << "collect results." << std::endl;
    int calc_add = OutputPipe::read(q);

    std::cout << "Add sum: " << calc_add << ", expected (" << expectedSum << ")"
              << std::endl;
    if (calc_add != expectedSum) {
      passed = false;
    }

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

  std::cout << (passed ? "PASSED" : "FAILED") << std::endl;

  return passed ? EXIT_SUCCESS : EXIT_FAILURE;
}
