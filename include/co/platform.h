#ifndef CO_PLATFORM_H
#define CO_PLATFORM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum co_architecture {
    CO_ARCH_UNKNOWN = 0,
    CO_ARCH_X86,
    CO_ARCH_X86_64,
    CO_ARCH_ARM32,
    CO_ARCH_AARCH64,
    CO_ARCH_RISCV32,
    CO_ARCH_RISCV64,
    CO_ARCH_E2K
} co_architecture_t;

typedef struct co_platform_info {
    co_architecture_t architecture;
    uint32_t pointer_bits;
    uint32_t little_endian;
    uint32_t elf_machine;
} co_platform_info_t;

/* Reports compile-target properties; it does not probe optional CPU features. */
co_platform_info_t co_platform_detect(void);
const char *co_architecture_name(co_architecture_t architecture);

#ifdef __cplusplus
}
#endif
#endif
