# E2K / Elbrus platform profile

This profile enables 64-bit little-endian E2K Linux user-space builds with MCST LCC. ELF machine: `EM_MCST_ELBRUS = 175`; Linux `uname -m = e2k`.

- Native builds use Elbrus Linux, LCC and matching runtime libraries.
- Cross builds use x86_64 Linux, the MCST LCC cross system and target sysroot.
- CMake toolchain: `cmake/toolchains/e2k-linux-lcc.cmake`.
- Select the compiler with `E2K_LCC` or `E2K_CC`; optional sysroot: `E2K_SYSROOT`.

The deployment route covered here is a native Linux process. On hardware, the MCST Program of Initial Start (PNS) initializes the board and starts Elbrus Linux; the project runs after Linux starts.

`qemu-e2k` is user-mode Linux application emulation, not an Elbrus system/firmware emulator. Generic Limine does not list E2K as a supported architecture; an x86 boot image is not an E2K boot image. A bare-metal kernel port needs the PNS/kernel image contract and E2K-specific entry, memory, interrupt and device code.

Elbrus Linux families include v2-v7. Vendor SDK targets are model-specific. The published QEMU user-emulator manual lists v2-v6 and does not qualify v7 emulation. Cross-compile success is not runtime proof; qualify on a native E2K runner or hardware.

References: [MCST downloads](https://dev.mcst.ru/download/), [SDK](https://www.mcst.ru/SDK), [Elbrus Linux](https://www.mcst.ru/elbrus_linux), [PNS](https://www.mcst.ru/boot), [qemu-e2k](https://www.mcst.ru/2025-12-25_qemu-e2k), [Limine architectures](https://github.com/Limine-Bootloader/Limine).
