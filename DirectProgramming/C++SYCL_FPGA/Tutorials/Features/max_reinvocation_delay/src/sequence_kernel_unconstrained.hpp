#include <sycl/ext/intel/fpga_extensions.hpp>
#include <sycl/sycl.hpp>

// Forward declare the kernel and pipe names
// (This prevents unwanted name mangling in the optimization report.)
class SequenceUnconstrained;
class ResultsUnconstrained;

// Results pipe from device back to host
using PipeResultsUnconstrained =
    sycl::ext::intel::experimental::pipe<ResultsUnconstrained, int>;

// Computes and outputs the first "sequence_length" terms of the arithmetic
// sequences with first term "first_term" and factors 1 through kFactors.
template <int kFactors>
struct SequenceKernelUnconstrained {
  int first_term;
  int sequence_length;

  void operator()() const {
    for (int factor = 1; factor <= kFactors; factor++) {
      for (int i = 0; i < sequence_length; i++) {
        PipeResultsUnconstrained::write(first_term + i * factor);
      }
    }
  }
};