#include "co/dependency.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    const uint32_t dag[4] = {
        0u, UINT32_C(1) << 0, UINT32_C(1) << 0,
        (UINT32_C(1) << 1) | (UINT32_C(1) << 2)
    };
    const uint32_t cycle[3] = {
        UINT32_C(1) << 1, UINT32_C(1) << 0, UINT32_C(1) << 1
    };
    uint32_t order[4] = {99u, 99u, 99u, 99u};
    uint32_t blocked = 99u;

    assert(co_dependency_plan(dag, 4u, order, &blocked) == CO_DEPENDENCY_OK);
    assert(order[0] == 0u && order[1] == 1u &&
           order[2] == 2u && order[3] == 3u);
    assert(blocked == 0u);

    assert(co_dependency_plan(cycle, 3u, order, &blocked) == CO_DEPENDENCY_ECYCLE);
    assert(blocked == 7u);
    assert(co_dependency_plan(dag, 0u, order, &blocked) == CO_DEPENDENCY_EINVAL);
    assert(co_dependency_plan(NULL, 4u, order, &blocked) == CO_DEPENDENCY_EINVAL);

    {
        const uint32_t invalid[2] = {UINT32_C(1) << 3, 0u};
        assert(co_dependency_plan(invalid, 2u, order, &blocked) == CO_DEPENDENCY_EINVAL);
    }

    puts("CO dependency tests: PASS");
    return 0;
}
