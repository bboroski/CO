#include "co/consensus.h"

#include <stddef.h>

co_result_t co_consensus_evaluate(
    const co_vote_t *votes,
    size_t vote_count,
    uint32_t expected_epoch,
    uint32_t quorum,
    co_consensus_result_t *result)
{
    size_t i;
    size_t j;
    uint32_t eligible = 0U;
    uint32_t stale = 0U;
    uint32_t best_count = 0U;
    uint32_t best_proposal = 0U;
    int tied = 0;

    if (votes == NULL || result == NULL || vote_count == 0U ||
        vote_count > CO_CONSENSUS_MAX_VOTES || quorum == 0U ||
        quorum > vote_count || quorum <= (uint32_t)(vote_count / 2U)) {
        return CO_EINVAL;
    }

    result->state = CO_CONSENSUS_INVALID;
    result->proposal_id = 0U;
    result->agreeing_nodes = 0U;
    result->eligible_nodes = 0U;
    result->stale_votes = 0U;

    for (i = 0U; i < vote_count; ++i) {
        if (votes[i].valid == 0U) {
            continue;
        }
        if (votes[i].node_id == 0U || votes[i].proposal_id == 0U) {
            return CO_EINVAL;
        }
        for (j = 0U; j < i; ++j) {
            if (votes[j].valid != 0U &&
                votes[j].node_id == votes[i].node_id) {
                return CO_EINVAL;
            }
        }
        if (votes[i].epoch != expected_epoch) {
            stale++;
        } else {
            eligible++;
        }
    }

    for (i = 0U; i < vote_count; ++i) {
        uint32_t count = 0U;
        if (votes[i].valid == 0U || votes[i].epoch != expected_epoch) {
            continue;
        }
        for (j = 0U; j < vote_count; ++j) {
            if (votes[j].valid != 0U &&
                votes[j].epoch == expected_epoch &&
                votes[j].proposal_id == votes[i].proposal_id) {
                count++;
            }
        }
        if (count > best_count) {
            best_count = count;
            best_proposal = votes[i].proposal_id;
            tied = 0;
        } else if (count == best_count && count != 0U &&
                   votes[i].proposal_id != best_proposal) {
            tied = 1;
        }
    }

    result->eligible_nodes = eligible;
    result->stale_votes = stale;
    result->agreeing_nodes = best_count;

    if (best_count >= quorum) {
        result->state = CO_CONSENSUS_AGREED;
        result->proposal_id = best_proposal;
    } else if (tied != 0) {
        result->state = CO_CONSENSUS_CONFLICT;
    } else {
        result->state = CO_CONSENSUS_NO_QUORUM;
    }

    return CO_OK;
}
