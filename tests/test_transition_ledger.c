#include "co/transition_ledger.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    co_transition_ledger_t ledger;
    co_transition_event_t snapshot[CO_TRANSITION_CAPACITY];
    size_t i, count;
    co_transition_ledger_init(&ledger);
    assert(co_transition_ledger_append(&ledger, 10u, 1u, 7u, 1u, 900u, CO_TRANSITION_FLAG_OBSERVED, 0u) == 1);
    assert(co_transition_ledger_append(&ledger, 11u, 2u, 7u, 2u, 800u,
        CO_TRANSITION_FLAG_OBSERVED | CO_TRANSITION_FLAG_CORROBORATED, 1u) == 1);
    assert(co_transition_ledger_append(&ledger, 9u, 3u, 7u, 1u, 500u, CO_TRANSITION_FLAG_OBSERVED, 0u) == 0);
    assert(co_transition_ledger_append(&ledger, 12u, 3u, 7u, 1u, 1001u, CO_TRANSITION_FLAG_OBSERVED, 0u) == 0);
    assert(co_transition_ledger_append(&ledger, 12u, 3u, 7u, 1u, 500u, CO_TRANSITION_FLAG_CORROBORATED, 0u) == 0);
    assert(co_transition_ledger_append(&ledger, 12u, 3u, 7u, 1u, 500u, CO_TRANSITION_FLAG_OBSERVED, ledger.next_sequence) == 0);
    assert(co_transition_ledger_snapshot(&ledger, NULL, 0u) == 2u);
    count = co_transition_ledger_snapshot(&ledger, snapshot, CO_TRANSITION_CAPACITY);
    assert(count == 2u && snapshot[0].sequence == 1u && snapshot[1].sequence == 2u);
    for (i = 0u; i < CO_TRANSITION_CAPACITY + 3u; ++i)
        assert(co_transition_ledger_append(&ledger, 20u + (uint64_t)i, 10u + (uint32_t)i,
            7u, 0u, 1000u, CO_TRANSITION_FLAG_OBSERVED, 0u) == 1);
    assert(ledger.count == CO_TRANSITION_CAPACITY && ledger.dropped == 5u);
    count = co_transition_ledger_snapshot(&ledger, snapshot, CO_TRANSITION_CAPACITY);
    assert(count == CO_TRANSITION_CAPACITY && snapshot[0].sequence == 8u);
    puts("bounded event history tests passed");
    return 0;
}
