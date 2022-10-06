# FPGA Template

This project serves as a template for Intel® oneAPI FPGA designs. 

| Optimized for                     | Description
|:---                               |:---
| OS                                | Linux* Ubuntu* 18.04/20.04 <br> RHEL*/CentOS* 8 <br> SUSE* 15 <br> Windows* 10
| Hardware                          | Intel® FPGA Programmable Acceleration Card (PAC) D5005 (with Intel Stratix® 10 SX) <br> Intel® FPGA 3rd party / custom platforms with oneAPI support <br> *__Note__: Intel® FPGA PAC hardware is only compatible with Ubuntu 18.04*
| Software                          | Intel® oneAPI DPC++ Compiler <br> Intel® Quartus Prime Pro Edition <br> Siemens® Questa® Intel® FPGA Starter Edition
| What you will learn               | Best practices for creating and managing a oneAPI FPGA project
| Time to complete                  | 10 minutes

## Purpose

Use this project as a starting point when you build designs for the Intel® oneAPI FPGA compiler. It includes a CMake build system to abstract away the need to know all the various command-line flags for the `icpx` compiler, and a simple single-source design to serve as an example. You can customize the build flags by modifying the top part of `src/CMakeLists.txt`. If you want to pass additional flags to Intel DPC++ compiler, you can change the `USER_FLAGS` and `USER_HARDWARE_FLAGS` variables defined in `src/CMakeLists.txt`. 

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

# When targeting a board, the `FPGA_BOARD` will be targeted. Options are:
#   intel_s10sx_pac:pac_s10
#   intel_s10sx_pac:pac_s10_usm
#   intel_a10gx_pac:pac_a10
set(FPGA_BOARD "intel_s10sx_pac:pac_s10_usm")

set(USER_HARDWARE_FLAGS "")
# use cmake -DUSER_HARDWARE_FLAGS=<flags> to set extra flags for FPGA backend
# compilation

set(USER_FLAGS "")
# use cmake -DUSER_FLAGS=<flags> to set extra flags for general compilation
```

Everything below this in the `src/CMakeLists.txt` is necessary for selecting the compiler flags that are necessary to support the build targets specified below, and should not need to be modified.

## License
Code samples are licensed under the MIT license. See
[License.txt](https://github.com/oneapi-src/oneAPI-samples/blob/master/License.txt) for details.

Third party program Licenses can be found here: [third-party-programs.txt](https://github.com/oneapi-src/oneAPI-samples/blob/master/third-party-programs.txt).

## Building the FPGA Template Tutorial
Use these commands to run the design, depending on your OS.

### On a Linux* System 
This design uses CMake to build the project, generate build artifacts for GNU/make like this:

```bash
mkdir build
cd build
cmake ..
```

This project can build 8 targets for Linux.

| Target          | Expected Time  | Output                                                        | Description                                                                                                                                                                                                                                                                                             |
|-----------------|----------------|---------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `make fpga_emu` | Seconds        | x86-64 binary                                                 | Compiles the FPGA device code to the CPU. Use the Intel® FPGA Emulation Platform for OpenCL™ software to verify your SYCL code’s functional correctness.                                                                                                                                                |
| `make report`   | Minutes        | RTL                                                           | Compiles the FPGA device code to RTL and generates an optimization report that describes the structures generated on the FPGA, identifies performance bottlenecks, and estimates resource utilization. This report will include the interfaces defined in your selected Board Support Package.          |
| `make fpga`     | Multiple Hours | Quartus Place & Route (Full accelerator) + x86-64 host binary | Compiles the FPGA device code to RTL and generate an FPGA image that you can run on a supported accelerator board.                                                                                                                                                                                      |
| `make fpga_sim` | Minutes        | RTL + x86-64 binary                                           | Compiles the FPGA device code to RTL and generates a simulation testbench. Use the Questa*-Intel® FPGA Edition simulator to verify your design.                                                                                                                                                         |

The `fpga_emu`, `fpga_sim` and `fpga` targets produce binaries that you can run. The executables will be called `TARGET_NAME.fpga_emu`, `TARGET_NAME.fpga_sim`, and `TARGET_NAME.fpga`, where `TARGET_NAME` is the value you specify in `src/CMakeLists.txt`.

### On a Windows* System
This design uses CMake to build the project, and generate build artifacts for `nmake` like this:

```bash
mkdir build
cd build
cmake -G "NMake Makefiles" ..
```

This project can build 8 targets for Windows.

| Target           | Expected Time  | Output                                                        | Description                                                                                                                                                                                                                                                                                    |
|------------------|----------------|---------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `nmake fpga_emu` | Seconds        | x86-64 binary                                                 | Compiles the FPGA device code to the CPU. Use the Intel® FPGA Emulation Platform for OpenCL™ software to verify your SYCL code’s functional correctness.                                                                                                                                       |
| `nmake report`   | Minutes        | RTL                                                           | Compiles the FPGA device code to RTL and generates an optimization report that describes the structures generated on the FPGA, identifies performance bottlenecks, and estimates resource utilization. This report will include the interfaces defined in your selected Board Support Package. |
| `nmake fpga`     | Multiple Hours | Quartus Place & Route (Full accelerator) + x86-64 host binary | Compiles the FPGA device code to RTL and generate an FPGA image that you can run on a supported accelerator board.                                                                                                                                                                             |
| `nmake fpga_sim` | Minutes        | RTL + x86-64 binary                                           | Compiles the FPGA device code to RTL and generates a simulation testbench. Use the Questa*-Intel® FPGA Edition simulator to verify your design.                                                                                                                                                |

The `fpga_emu`, `fpga_sim`, and `fpga` targets also produce binaries that you can run. The executables will be called `TARGET_NAME.fpga_emu.exe`, `TARGET_NAME.fpga_sim.exe`, and `TARGET_NAME.fpga.exe`, where `TARGET_NAME` is the value you specify in `src/CMakeLists.txt`.
