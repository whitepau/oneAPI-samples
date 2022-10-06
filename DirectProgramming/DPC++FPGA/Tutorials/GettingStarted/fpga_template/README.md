FPGA Template
=============

This project serves as a template for oneAPI FPGA designs. Feel free to clone it
and use it to start your projects off on the right foot!

## Description

You can customize the build flags by editing the top part of
`src/CMakeLists.txt`. If you want to pass additional flags to `dpcpp`, you can
change the `USER_FLAGS` and `USER_HARDWARE_FLAGS` variables defined in
`src/CMakeLists.txt`. 

| Variable              | Description                                                                                                                                                                       |
|-----------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `USER_HARDWARE_FLAGS` | These flags apply only to flows that generate FPGA hardware (i.e. report, simulation, hardware). You can specify flags such as `-Xsclock` or `-Xshyper-optimized-handshaking=off` |
| `USER_FLAGS`          | These flags apply to all flows, including emulation. You can specify flags such as `-v` or define macros such as `-DYOUR_OWN_MACRO=3`                                             |

```bash
###############################################################################
### Customize these build variables
###############################################################################
set(SOURCE_FILE vector_add.cpp)
set(TARGET_NAME vector_add)

# When generating a standalone IP, the `FPGA_DEVICE` will be targeted. You can
# specify a device family (E.g. "Arria10" or "Stratix10") or a specific part
# number (E.g. "10AS066N3F40E2SG")
set(FPGA_DEVICE "Stratix10")

# When targeting a board, the `FPGA_BOARD` will be targeted. Options are:
#   intel_s10sx_pac:pac_s10
#   intel_s10sx_pac:pac_s10_usm
#   intel_a10gx_pac:pac_a10
set(FPGA_BOARD "intel_s10sx_pac:pac_s10_usm")

set(USER_HARDWARE_FLAGS "")
# use cmake -DUSER_HARDWARE_FLAGS=<flags> to set extra flags for FPGA backend
# compilation

set(IPA_EXPERIMENTAL_INCLUDE "-I\"$ENV{INTELFPGAOCLSDKROOT}/include\"")
set(USER_FLAGS "${IPA_EXPERIMENTAL_INCLUDE}")
# use cmake -DUSER_FLAGS=<flags> to set extra flags for general compilation
```

## Running the Design
Use these commands to run the design, depending on your OS.

### Linux
For best results, use Linux. This design uses CMake to build the project, generate build artifacts for GNU/make like this:

```bash
mkdir build
cd build
cmake ..
```

This project can build 8 targets for Linux.

| Target                     | Expected Time  | Output                                                        | Description                                                                                                                                                                                                                                                                                             |
|----------------------------|----------------|---------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `make fpga_emu`            | Seconds        | x86-64 binary                                                 | Compiles the FPGA device code to the CPU. Use the Intel® FPGA Emulation Platform for OpenCL™ software to verify your SYCL code’s functional correctness.                                                                                                                                                |
| `make fpga_ip_report`      | Minutes        | RTL                                                           | Compiles the FPGA device code to RTL and generates an optimization report that describes the structures generated on the FPGA, identifies performance bottlenecks, and estimates resource utilization.                                                                                                  |
| `make fpga_ip_sim`         | Minutes        | RTL + x86-64 binary                                           | Compiles the FPGA device code to RTL and generates a simulation testbench. Use the Questa*-Intel® FPGA Edition simulator to verify your design.                                                                                                                                                         |
| `make fpga_ip`             | Minutes        | RTL                                                           | Compiles the FPGA device code to RTL and generates an optimization report that describes the structures generated on the FPGA, identifies performance bottlenecks, and estimates resource utilization. This RTL may be used in a Quartus project because it uses `-fsycl-device-code-split=per_kernel`. |
| `make fpga_ip_qii`         | < 1 hour       | Quartus Place & Route (IP Only)                               | Compiles the FPGA device code to RTL and run Quartus Place & Route to get accurate area/performance estimates of your IP. This RTL may be used in a Quartus project because it uses `-fsycl-device-code-split=per_kernel`.                                                                              |
| `make fpga_board_report`   | Minutes        | RTL                                                           | Compiles the FPGA device code to RTL and generates an optimization report that describes the structures generated on the FPGA, identifies performance bottlenecks, and estimates resource utilization. This report will include the interfaces defined in your selected Board Support Package.          |
| `make fpga_board`          | Multiple Hours | Quartus Place & Route (Full accelerator) + x86-64 host binary | Compiles the FPGA device code to RTL and generate an FPGA image that you can run on a supported accelerator board.                                                                                                                                                                                      |
| `make fpga_board_sim`      | Minutes        | RTL + x86-64 binary                                           | Compiles the FPGA device code to RTL and generates a simulation testbench. Use the Questa*-Intel® FPGA Edition simulator to verify your design.                                                                                                                                                         |

The `fpga_emu`, `fpga_ip_sim`, `fpga_board_sim` and `fpga_board` targets also
produce binaries that you can run. The executables will be called
`TARGET_NAME.fpga_emu`, `TARGET_NAME.fpga_ip_sim`, `TARGET_NAME.fpga_board_sim`,
and `TARGET_NAME.fpga_board`, where `TARGET_NAME` is the value you specify in
`src/CMakeLists.txt`.

### Windows
This design uses CMake to build the project, generate build artifacts for nmake like this:

```bash
mkdir build
cd build
cmake -G "NMake Makefiles" ..
```

This project can build 8 targets for Windows.

| Target                      | Expected Time  | Output                                                        | Description                                                                                                                                                                                                                                                                                    |
|-----------------------------|----------------|---------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `nmake fpga_emu`            | Seconds        | x86-64 binary                                                 | Compiles the FPGA device code to the CPU. Use the Intel® FPGA Emulation Platform for OpenCL™ software to verify your SYCL code’s functional correctness.                                                                                                                                       |
| `nmake fpga_ip_report`      | Minutes        | RTL                                                           | Compiles the FPGA device code to RTL and generates an optimization report that describes the structures generated on the FPGA, identifies performance bottlenecks, and estimates resource utilization.                                                                                         |
| `nmake fpga_ip_sim`         | Minutes        | RTL + x86-64 binary                                           | Compiles the FPGA device code to RTL and generates a simulation testbench. Use the Questa*-Intel® FPGA Edition simulator to verify your design.                                                                                                                                                |
| `nmake fpga_ip`             | Minutes        | RTL                                                           | Compiles the FPGA device code to RTL and generates an optimization report that describes the structures generated on the FPGA, identifies performance bottlenecks, and estimates resource utilization. This RTL may be used in a Quartus project because it uses `-fsycl-device-code-split=per_kernel`. |
| `nmake fpga_ip_qii`         | < 1 hour       | Quartus Place & Route (IP Only)                               | Compiles the FPGA device code to RTL and run Quartus Place & Route to get accurate area/performance estimates of your IP. This RTL may be used in a Quartus project because it uses `-fsycl-device-code-split=per_kernel`.                                                                              |
| `nmake fpga_board_report`   | Minutes        | RTL                                                           | Compiles the FPGA device code to RTL and generates an optimization report that describes the structures generated on the FPGA, identifies performance bottlenecks, and estimates resource utilization. This report will include the interfaces defined in your selected Board Support Package. |
| `nmake fpga_board`          | Multiple Hours | Quartus Place & Route (Full accelerator) + x86-64 host binary | Compiles the FPGA device code to RTL and generate an FPGA image that you can run on a supported accelerator board.                                                                                                                                                                             |
| `nmake fpga_board_sim`      | Minutes        | RTL + x86-64 binary                                           | Compiles the FPGA device code to RTL and generates a simulation testbench. Use the Questa*-Intel® FPGA Edition simulator to verify your design.                                                                                                                                                |

The `fpga_emu`, `fpga_ip_sim`, `fpga_board_sim` and `fpga_board` targets also
produce binaries that you can run. The executables will be called
`TARGET_NAME.fpga_emu`, `TARGET_NAME.fpga_ip_sim`, `TARGET_NAME.fpga_board_sim`,
and `TARGET_NAME.fpga_board`, where `TARGET_NAME` is the value you specify in
`src/CMakeLists.txt`.
