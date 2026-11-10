#include "co/platform.h"

#include <stdint.h>

co_platform_info_t co_platform_detect(void)
{
    co_platform_info_t info = {CO_ARCH_UNKNOWN, (uint32_t)(sizeof(void *) * 8u), 0u, 0u};
    const uint16_t marker = 1u;
    info.little_endian = (*(const uint8_t *)&marker == 1u) ? 1u : 0u;
#if defined(__e2k__)
    info.architecture = CO_ARCH_E2K;
    info.elf_machine = 175u;
#elif defined(__x86_64__) || defined(_M_X64)
    info.architecture = CO_ARCH_X86_64;
#elif defined(__i386__) || defined(_M_IX86)
    info.architecture = CO_ARCH_X86;
#elif defined(__aarch64__) || defined(_M_ARM64)
    info.architecture = CO_ARCH_AARCH64;
#elif defined(__arm__) || defined(_M_ARM)
    info.architecture = CO_ARCH_ARM32;
#elif defined(__riscv) && __riscv_xlen == 64
    info.architecture = CO_ARCH_RISCV64;
#elif defined(__riscv) && __riscv_xlen == 32
    info.architecture = CO_ARCH_RISCV32;
#endif
    return info;
}

const char *co_architecture_name(co_architecture_t architecture)
{
    switch (architecture) {
        case CO_ARCH_X86: return "x86";
        case CO_ARCH_X86_64: return "x86_64";
        case CO_ARCH_ARM32: return "arm";
        case CO_ARCH_AARCH64: return "aarch64";
        case CO_ARCH_RISCV32: return "riscv32";
        case CO_ARCH_RISCV64: return "riscv64";
        case CO_ARCH_E2K: return "e2k";
        case CO_ARCH_UNKNOWN:
        default: return "unknown";
    }
}
