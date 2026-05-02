# riscv-linux-boot

## RISC-V Full-Stack Linux Development Guide

This project demonstrates the complete implementation of a custom Linux-based operating system on a simulated RISC-V 64-bit SoC. It covers hardware emulation, firmware integration, kernel configuration, and kernel-space driver development.

### 1. Environment Setup & Hardware Emulation

The project utilizes QEMU to emulate the virt machine, providing a virtual RISC-V CPU, 256MB of RAM, and UART peripherals.

Installation:

sudo apt-get update\
sudo apt-get install qemu-system\
qemu-system-riscv64 --version\

Initial Verification:

qemu-system-riscv64 -M virt -m 256M -nographic -bios none
Note: A "hang" at this stage indicates successful memory allocation and CPU startup, stalled at the reset vector without instructions.

### 2. Toolchain & Firmware Layer
Cross-compilation is essential for developing RISC-V software on x86/AMD64 architectures.

Cross-Compiler: sudo apt install gcc-riscv64-linux-gnu.

OpenSBI: Acts as the "BIOS," handling hardware initialization in M-mode.

Build Command: make PLATFORM=generic CROSS_COMPILE=riscv64-linux-gnu-.

Binary: fw_jump.bin.

### 3. The Kernel Layer: Custom Linux Build
A 64-bit Linux kernel was cross-compiled and configured for the virt platform.

Source: Upstream Linux Stable.

Configuration: make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- defconfig.

Compilation: make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- -j$(nproc).

Output: arch/riscv/boot/Image.

### 4. The Filesystem Layer: BusyBox
The RootFS provides the user-space environment. BusyBox is utilized as a static binary for maximum efficiency in an embedded context.

Critical RootFS Steps:
Directory Structure: Manual creation of dev, proc, sys, and etc/init.d.

Init Script (rcS): Automates mounting of virtual filesystems and starts the shell.

Device Nodes: Manual creation of /dev/null and /dev/console using mknod to ensure stable I/O.
Packaging:

find . | cpio -o -H newc | gzip > ../rootfs.img.gz

### 5. Kernel-Space Innovation: Timer Driver
To demonstrate hardware-software interaction, a custom Loadable Kernel Module (LKM) was developed to handle timer interrupts.
Functionality: Uses the Linux Timer API to process asynchronous external interrupts.
Deployment: The driver (timer_driver.ko) is loaded into the running kernel using insmod.
Verification: Interrupt handling is confirmed via kernel log outputs (dmesg).

### 6. Final Execution
The entire stack—OpenSBI, Linux Kernel, and RootFS—is launched via QEMU:

qemu-system-riscv64 -M virt -m 256M -nographic \
    -bios fw_jump.bin \
    -kernel Image \
    -initrd rootfs.img.gz \
    -append "root=/dev/ram rdinit=/init console=ttyS0"
    
Project Outcome: Successfully booted a custom Linux kernel on emulated RISC-V hardware with functional user-space applications and kernel-space interrupt handling.
