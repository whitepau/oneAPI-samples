###############################################################################
### Customize these build variables
###############################################################################
set(SOURCE_FILE fpga_template.cpp)
set(TARGET_NAME fpga_template)

# use cmake -DFPGA_DEVICE=<board-support-package>:<board-variant> to choose a
# different device. Here are a few device examples:
#   intel_s10sx_pac:pac_s10
#   intel_s10sx_pac:pac_s10_usm
#   intel_a10gx_pac:pac_a10
# Note that depending on your installation, you may need to specify the full 
# path to the board support package (BSP), this usually is in your install 
# folder.
set(FPGA_DEVICE "intel_s10sx_pac:pac_s10_usm")

# use cmake -DUSER_HARDWARE_FLAGS=<flags> to set extra flags for FPGA backend
# compilation
set(USER_HARDWARE_FLAGS "")

# use cmake -DUSER_FLAGS=<flags> to set extra flags for general compilation
set(USER_FLAGS "")
###############################################################################
### no changes after here
###############################################################################

# define the different build targets the generated build script will support.
set(EMULATOR_TARGET ${TARGET_NAME}.fpga_emu)
set(REPORT_TARGET ${TARGET_NAME}.fpga_report)
set(SIMULATOR_TARGET ${TARGET_NAME}.fpga_sim)
set(FPGA_TARGET ${TARGET_NAME}.fpga)

# FPGA device selection
if(DEFINED FPGA_DEVICE)
    message(STATUS "Configuring the design to run on ${FPGA_DEVICE}")
endif()

# This is a Windows-specific flag that enables exception handling in host code
if(WIN32)
    # add qactypes to link command on Windows only
    set(QACTYPES_LINK "-qactypes")
endif()

# A DPC++ ahead-of-time (AoT) compile processes the device code in two stages.
# 1. The "compile" stage compiles the device code to an intermediate
#    representation (SPIR-V).
# 2. The "link" stage invokes the compiler's FPGA backend before linking. For
#    this reason, FPGA backend flags must be passed as link flags in CMake.
set(EMULATOR_COMPILE_FLAGS "-fsycl -fintelfpga -Wall -qactypes")
set(EMULATOR_LINK_FLAGS    "-fsycl -fintelfpga ${QACTYPES_LINK}")
set(HARDWARE_COMPILE_FLAGS "-fsycl -fintelfpga -Wall -qactypes")
set(BOARD_LINK_FLAGS       "-fsycl -fintelfpga -Xstarget=${FPGA_DEVICE}   ${USER_HARDWARE_FLAGS} ${QACTYPES_LINK}")

###############################################################################
### FPGA Emulator
###############################################################################
# To compile in a single command:
#    dpcpp -fintelfpga -DFPGA_EMULATOR fpga_compile.cpp -o fpga_compile.fpga_emu
# CMake executes:
#    [compile] dpcpp -fintelfpga -DFPGA_EMULATOR -o fpga_compile.cpp.o -c fpga_compile.cpp
#    [link]    dpcpp -fintelfpga fpga_compile.cpp.o -o fpga_compile.fpga_emu
add_executable(${EMULATOR_TARGET} ${SOURCE_FILE})
add_custom_target(fpga_emu DEPENDS ${EMULATOR_TARGET})
set_target_properties(${EMULATOR_TARGET} PROPERTIES COMPILE_FLAGS "${EMULATOR_COMPILE_FLAGS} -DFPGA_EMULATOR ${USER_FLAGS}")
set_target_properties(${EMULATOR_TARGET} PROPERTIES LINK_FLAGS "${EMULATOR_LINK_FLAGS} -DFPGA_EMULATOR ${USER_FLAGS}")

###############################################################################
### Report
###############################################################################
# To compile manually:
#   dpcpp -fintelfpga -Xshardware -Xstarget=<FPGA_DEVICE> -fsycl-link=early fpga_compile.cpp -o fpga_compile.report.a
set(REPORT_TARGET ${TARGET_NAME}.report.a)
# The compile output is not an executable, but an intermediate compilation result unique to DPC++.
add_executable(${REPORT_TARGET} ${SOURCE_FILE})
add_custom_target(report DEPENDS ${REPORT_TARGET})
set_target_properties(${REPORT_TARGET} PROPERTIES COMPILE_FLAGS "${HARDWARE_COMPILE_FLAGS} -DFPGA_HARDWARE ${USER_FLAGS}")
set_target_properties(${REPORT_TARGET} PROPERTIES LINK_FLAGS "${BOARD_LINK_FLAGS} ${USER_FLAGS} -Xshardware -fsycl-link=early")
# fsycl-link=early stops the compiler after RTL generation, before invoking Quartus®

###############################################################################
### FPGA Board Simulation
###############################################################################
# To compile in a single command:
#   dpcpp -fintelfpga -Xstarget=<FPGA_DEVICE> -Xssimulation -Xsghdl=1 fpga_compile.cpp -o fpga_compile.fpga_sim
# CMake executes:
#   [compile] dpcpp -fintelfpga -o fpga_compile.cpp.o -c fpga_compile.cpp
#   [link]    dpcpp -fintelfpga -Xstarget=<FPGA_DEVICE> -Xssimulation -Xsghdl=1 fpga_compile.cpp.o -o fpga_compile.fpga_sim
add_executable(${SIMULATOR_TARGET} EXCLUDE_FROM_ALL ${SOURCE_FILE})
add_custom_target(fpga_sim DEPENDS ${SIMULATOR_TARGET})
set_target_properties(${SIMULATOR_TARGET} PROPERTIES COMPILE_FLAGS "${HARDWARE_COMPILE_FLAGS} -DFPGA_SIMULATOR ${USER_FLAGS}")
set_target_properties(${SIMULATOR_TARGET} PROPERTIES LINK_FLAGS "${BOARD_LINK_FLAGS} -Xssimulation -Xsghdl=1 ${USER_FLAGS}")

###############################################################################
### FPGA Board
###############################################################################
# To compile in a single command:
#   dpcpp -fintelfpga -Xshardware -Xstarget=<FPGA_DEVICE> fpga_compile.cpp -o fpga_compile.fpga
# CMake executes:
#   [compile] dpcpp -fintelfpga -o fpga_compile.cpp.o -c fpga_compile.cpp
#   [link]    dpcpp -fintelfpga -Xshardware -Xstarget=<FPGA_DEVICE> fpga_compile.cpp.o -o fpga_compile.fpga
add_executable(${FPGA_TARGET} EXCLUDE_FROM_ALL ${SOURCE_FILE})
add_custom_target(fpga DEPENDS ${FPGA_TARGET})
set_target_properties(${FPGA_TARGET} PROPERTIES COMPILE_FLAGS "${HARDWARE_COMPILE_FLAGS} -DFPGA_HARDWARE ${USER_FLAGS}")
set_target_properties(${FPGA_TARGET} PROPERTIES LINK_FLAGS "${BOARD_LINK_FLAGS} -Xshardware ${USER_FLAGS}")
