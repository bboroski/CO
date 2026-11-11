#ifndef CO_DEPENDENCY_H
#define CO_DEPENDENCY_H

#include <stddef.h>
#include <stdint.h>

#define CO_DEPENDENCY_MAX_NODES 32u

typedef enum co_dependency_status {
    CO_DEPENDENCY_OK = 0,
    CO_DEPENDENCY_EINVAL = -1,
    CO_DEPENDENCY_ECYCLE = -2
} co_dependency_status_t;

/*
 * Produce a stable dependency-first order from one 32-bit dependency mask
 * per node. This is a pure graph validator/planner; it never executes callbacks
 * or schedules components. On a cycle, blocked_mask identifies all unresolved
 * nodes (which can include nodes downstream of the cycle).
 */
static inline co_dependency_status_t co_dependency_plan(
    const uint32_t *dependencies,
    size_t count,
    uint32_t *order,
    uint32_t *blocked_mask)
{
    uint32_t valid_mask;
    uint32_t resolved = 0u;
    size_t position, node;

    if (dependencies == NULL || order == NULL || blocked_mask == NULL ||
        count == 0u || count > CO_DEPENDENCY_MAX_NODES) {
        return CO_DEPENDENCY_EINVAL;
    }
    valid_mask = count == CO_DEPENDENCY_MAX_NODES
                     ? UINT32_MAX
                     : (UINT32_C(1) << count) - 1u;
    for (node = 0u; node < count; ++node) {
        const uint32_t bit = UINT32_C(1) << node;
        if ((dependencies[node] & ~valid_mask) != 0u ||
            (dependencies[node] & bit) != 0u) {
            return CO_DEPENDENCY_EINVAL;
        }
    }

    for (position = 0u; position < count; ++position) {
        int found = 0;
        for (node = 0u; node < count; ++node) {
            const uint32_t bit = UINT32_C(1) << node;
            if ((resolved & bit) == 0u &&
                (dependencies[node] & ~resolved) == 0u) {
                order[position] = (uint32_t)node;
                resolved |= bit;
                found = 1;
                break;
            }
        }
        if (!found) {
            *blocked_mask = valid_mask & ~resolved;
            return CO_DEPENDENCY_ECYCLE;
        }
    }
    *blocked_mask = 0u;
    return CO_DEPENDENCY_OK;
}

#endif
