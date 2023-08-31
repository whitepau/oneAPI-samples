//  Copyright (c) 2022 Intel Corporation
//  SPDX-License-Identifier: MIT
//
// This design leverages a simple DMA oneAPI kernel that has had its RTL
// generated and integrated into the Nios V test system that will be used to
// control the accelerator. The DMA kernel has been configured to read from
// memory in memory location 0 (Buffer Location 0) and write to memory in memory
// location 1 (Buffer Location 1).
//
// The CPU is configured to have a single peripheral space located at
// 0x0010_0000 and it is 1MB in size.  So if you want to connect a different
// kernel/IP make sure to place it between data master address
// 0x0010_0000-0x001F_FFFF.

#include <stdio.h>
#include <stdlib.h>

// This comes from the BSP and contains Nios V data cache flushing APIs
#include <sys/alt_cache.h>

// This comes from the BSP that was generated by software_build.h, it includes
// the macros used to access the control/status registers of peripherals
#include "io.h"

// This comes from the BSP that was generated by software_build.h, it contains
// information like address map, IRQ mapping, etc...
#include "system.h"

// including the kernel register map directly from the kernel build directory
#include "../../../kernels/simple_dma/build/simple_dma.report.prj/include/register_map_offsets.hpp"

// In bytes, must be a multiple of 4.  Keep it a small number to shorten the
// simulation time and do not exceed the 1MB memory size (remember this code is
// in there too). Once the DMA gets going this buffer will fly by fast so
// setting it too high mostly affects the memory initialization and the
// correctness check at the end once the DMA gets going this buffer will fly by
// fast so setting it too high mostly affects the memory initialization and the
// correctness check at the end.
#define BUFFER_LENGTH 1024

// Error numbers
#define TEST_PASS 0
#define TEST_FAIL 1

/// Calculate DMA kernel register offsets from system.h, and the kernel register
/// offsets from register_map_offsets.hpp

#define REG_ARG_SOURCE_BASE \
  (SIMPLE_DMA_ACCELERATOR_BASE + ZTS9SIMPLEDMA_REGISTER_MAP_ARG_ARG_SOURCE_REG)

#define REG_ARG_DEST_BASE \
  (SIMPLE_DMA_ACCELERATOR_BASE + ZTS9SIMPLEDMA_REGISTER_MAP_ARG_ARG_DEST_REG)

#define REG_ARG_LENGTH_BASE      \
  (SIMPLE_DMA_ACCELERATOR_BASE + \
   ZTS9SIMPLEDMA_REGISTER_MAP_ARG_ARG_LENGTH_BYTES_REG)

#define REG_START_BASE \
  (SIMPLE_DMA_ACCELERATOR_BASE + ZTS9SIMPLEDMA_REGISTER_MAP_START_REG)

#define REG_STATUS \
  (SIMPLE_DMA_ACCELERATOR_BASE + ZTS9SIMPLEDMA_REGISTER_MAP_STATUS_REG)

/// @brief configure and start the Simple DMA Accelerator IP
///
/// @details `configure_and_start_dma` will accept the source, destination, and
/// transfer length and write them into the kernel CSRs using the old Nios
/// IORW/IORD_32DIRECT macros, since those also work for Nios II.
///
/// @note Since the kernel is located in the I/O space of the Nios V processor,
/// you may choose to simply dereference a pointer to bypass the data cache but
/// that doesn't port to Nios II directly so that has been avoided here.
///
/// @param[in] source Pointer to source memory to copy from
///
/// @param[in] destination Pointer to which to copy data
///
/// @param[in] length_bytes Number of bytes of data to copy
void configure_and_start_dma(unsigned int* source, unsigned int* destination,
                             unsigned int length_bytes) {
  // Nios V/g is 32-bit, but FPGA IP produced with the Intel® oneAPI DPC++/C++
  // Compiler uses 64-bit pointers, so we have to write the source pointer 32
  // bits at a time. The source pointer needs to be cast to unsigned int since
  // the Nios macros do not expect a pointer.

  // According to io.h there is an upper limitation of 12-bits of the offset
  // field, so this code instead adds the offset to the base (first argument of
  // macro) and hardcodes the offset field to 0 (second argument of macro).

  // DMA source
  IOWR_32DIRECT(REG_ARG_SOURCE_BASE, 0, (unsigned int)source);
  // padding upper 32 bits to all zeros
  IOWR_32DIRECT(REG_ARG_SOURCE_BASE + 4, 0, 0);

  // DMA destination
  IOWR_32DIRECT(REG_ARG_DEST_BASE, 0, (unsigned int)destination);
  // padding upper 32 bits to all zeros
  IOWR_32DIRECT(REG_ARG_DEST_BASE + 4, 0, 0);

  // DMA length
  IOWR_32DIRECT(REG_ARG_LENGTH_BASE, 0, BUFFER_LENGTH);

  // DMA start
  IOWR_32DIRECT(REG_START_BASE, 0, 1);

  // The DMA kernel should immediately start at this point
}

/// @brief Exercise the DMA kernel.
///
/// The test has the following phases: \n
///
/// 1. populate a source buffer with an incrementing pattern of 'BUFFER_LENGTH'
/// bytes \n
///
/// 2. clear out the destination buffer \n
///
/// 3. instruct the DMA kernel to perform the source --> destination transfer \n
///
/// 4. check that the destination contents match the source
///
/// @return 0 if the test passes.
int test_simple_dma() {
  // allocating source and destination buffers at compile time so that if too
  // large a value is set for BUFFER_LENGTH then we'll find out early at compile
  // time
  unsigned int source[BUFFER_LENGTH / 4];
  unsigned int destination[BUFFER_LENGTH / 4];
  int i;

  // initialize the source buffer with an incrementing pattern and clear out the
  // destination before the accelerator clobbers it
  for (i = 0; i < (BUFFER_LENGTH / 4); i++) {
    source[i] = i;
    destination[i] = 0;
  }

  // main memory (code_data_ram) is *not* in a peripheral region, so all the
  // writes to the source and destination need to be flushed from the data cache
  // to avoid cache coherency issues when the accelerator attempts to access
  // memory.

  // make sure all that source data that was set gets flushed out to main memory
  alt_dcache_flush(source, BUFFER_LENGTH);

  // make sure all that destination data that was zeroed out gets flushed out to
  // main memory
  alt_dcache_flush(destination, BUFFER_LENGTH);

  //  Configure and start the DMA kernel
  configure_and_start_dma(source, destination, BUFFER_LENGTH);

  // Busy-waiting for the accelerator to complete (kernel will fire off
  // interrupt as well but there is no register as of 2024.0 to clear it)
  while ((IORD_32DIRECT(REG_STATUS, 0) & KERNEL_REGISTER_MAP_DONE_MASK) !=
         KERNEL_REGISTER_MAP_DONE_MASK) {
  }

  // Now that the accelerator is done, test the destination buffer for
  // correctness. Since the destination buffer was already flushed from the data
  // cache, software can safely read the destination without additional data
  // flushes. Since the source was previously flushed as well, it will get
  // fetched from main memory and warm up the data cache just like the
  // destination buffer in the correctness loop.

  // test the results at the destination buffer, if a failure is detected set
  // pass to 0 and stop testing
  for (i = 0; i < (BUFFER_LENGTH / 4); i++) {
    if (source[i] != destination[i]) {
      printf(
          "Test Fail:  Source address = 0x%x, Destination address = 0x%x, byte "
          "offset 0x%x.  Read value 0x%x instead of expected value 0x%x.\n",
          (unsigned int)source, (unsigned int)destination, (i * 4),
          destination[i], source[i]);
      return TEST_FAIL;
    }
  }

  // If we reach this point then all the data must have passed so we can issue a
  // blanket statement that the entire test passed
  printf("Test Pass:  All the data at the destination matches the source.\n");

  return TEST_PASS;
}

/// @brief main function
///
/// @return 0 on a test pass and non-zero on failures, see error numbers near
/// top of this file.
int main() {
  int return_val;

  printf("Test design for the simple DMA kernel\n\n");
  printf(
      "Test will initialize %d incrementing four byte unsigned integers, have "
      "the accelerator DMA copy the data to a destination and then check the "
      "destination for correctness.\n",
      (BUFFER_LENGTH / 4));

  return_val = test_simple_dma();
  printf("Software will now exit.\n");
  return return_val;
}
