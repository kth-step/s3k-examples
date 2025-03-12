# 2partitions

This example project demonstrates how to create two partitions that share a UART device. The project involves two processes: Process 0 and Process 1.

- Process 0 serves as the boot process and the first partition.
- Process 1 is the second partition.

Process 0 initializes Process 1 and subsequently deletes all resources associated with it. Once Process 0 completes the setup for Process 1, the only explicitly shared resource between Process 0 and Process 1 will be the UART device. After both processes are set up, they print their respective process IDs to the UART device.

*Note: Process 0 and Process 1 may share memory subsystems such as cache, which means side-channels can still exist in the system. In other words, the two processes/partitions are not non-interferent. However, they cannot directly access or affect each other's resources.*

## Instructions

```
# Setup the build system
meson setup builddir --cross-file ../../cross/rv64imac.toml

# Compile the project
meson compile -C builddir

# Run program
./builddir/qemu.sh
```
