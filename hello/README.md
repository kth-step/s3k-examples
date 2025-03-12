# hello

This example project demonstrates a simple hello world program.

## Instructions

```
# Setup the build system
meson setup builddir --cross-file ../cross/rv64imac.toml

# Compile the project
meson compile -C builddir

# Run program
./builddir/qemu.sh
```
