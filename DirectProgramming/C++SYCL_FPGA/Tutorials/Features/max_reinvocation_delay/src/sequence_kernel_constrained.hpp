#include <sycl/ext/intel/fpga_extensions.hpp>
#include <sycl/sycl.hpp>

// Forward declare the kernel and pipe names
// (This prevents unwanted name mangling in the optimization report.)
class SequenceConstrained;
class ResultsConstrained;

// Results pipe from device back to host
using PipeResultsConstrained =
    sycl::ext::intel::experimental::pipe<ResultsConstrained, int>;

// Computes and outputs the first "sequence_length" terms of the arithmetic
// sequences with first term "first_term" and factors 1 through kFactors.
template <int kFactors>
struct SequenceKernelConstrained {
  int first_term;
  int sequence_length;

  void operator()() const {
    for (int factor = 1; factor <= kFactors; factor++) {
      [[intel::max_reinvocation_delay(1)]]  // NO-FORMAT: Attribute
      for (int i = 0; i < sequence_length; i++) {
        PipeResultsConstrained::write(first_term + i * factor);
      }
    }
  }
};