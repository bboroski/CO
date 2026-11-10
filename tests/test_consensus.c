#include "co/consensus.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    co_consensus_result_t result;
    const co_vote_t majority[] = {
        {1U, 10U, 7U, 1U}, {2U, 10U, 7U, 1U},
        {3U, 20U, 7U, 1U}, {4U, 10U, 6U, 1U}
    };
    const co_vote_t split[] = {
        {1U, 10U, 7U, 1U}, {2U, 10U, 7U, 1U},
        {3U, 20U, 7U, 1U}, {4U, 20U, 7U, 1U}
    };
    const co_vote_t duplicate[] = {
        {1U, 10U, 7U, 1U}, {1U, 20U, 7U, 1U}
    };

    assert(co_consensus_evaluate(majority, 4U, 7U, 3U, &result) == CO_OK);
    assert(result.state == CO_CONSENSUS_AGREED);
    assert(result.proposal_id == 10U);
    assert(result.eligible_nodes == 3U);
    assert(result.stale_votes == 1U);

    assert(co_consensus_evaluate(split, 4U, 7U, 3U, &result) == CO_OK);
    assert(result.state == CO_CONSENSUS_CONFLICT);

    assert(co_consensus_evaluate(duplicate, 2U, 7U, 2U, &result) == CO_EINVAL);
    assert(co_consensus_evaluate(majority, 4U, 7U, 2U, &result) == CO_EINVAL);
    assert(co_consensus_evaluate(NULL, 0U, 7U, 1U, &result) == CO_EINVAL);
    assert(co_consensus_evaluate(majority, 4U, 7U, 3U, NULL) == CO_EINVAL);

    puts("CO consensus tests passed");
    return 0;
}
