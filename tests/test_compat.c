#include "co/runtime.h"

#include <assert.h>

int main(void)
{
    co_runtime_t runtime;
    assert(co_runtime_start(&runtime) == CO_EINVAL);
    return 0;
}
