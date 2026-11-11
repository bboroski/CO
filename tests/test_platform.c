#include "co/platform.h"

#include <assert.h>
#include <string.h>

int main(void)
{
    co_platform_info_t info = co_platform_detect();
    assert(info.pointer_bits == 32u || info.pointer_bits == 64u);
    assert(info.little_endian <= 1u);
    assert(co_architecture_name(info.architecture) != NULL);
    if (info.architecture == CO_ARCH_E2K) {
        assert(info.pointer_bits == 64u);
        assert(info.little_endian == 1u);
        assert(info.elf_machine == 175u);
        assert(strcmp(co_architecture_name(info.architecture), "e2k") == 0);
    } else {
        assert(info.elf_machine == 0u);
    }
    return 0;
}
