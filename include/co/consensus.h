#ifndef CO_CONSENSUS_H
#define CO_CONSENSUS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CO_CONSENSUS_MAX_VOTES 64U

typedef enum {
    CO_CONSENSUS_INVALID = -1,
    CO_CONSENSUS_NO_QUORUM = 0,
    CO_CONSENSUS_AGREED = 1,
    CO_CONSENSUS_CONFLICT = 2
} co_consensus_state_t;

typedef struct {
    uint32_t node_id;
    uint32_t proposal_id;
    uint32_t epoch;
    uint8_t valid;
} co_vote_t;

typedef struct {
    co_consensus_state_t state;
    uint32_t proposal_id;
    uint32_t agreeing_nodes;
    uint32_t eligible_nodes;
    uint32_t stale_votes;
} co_consensus_result_t;

/* Deterministic tally only: no networking, identity verification or persistence. */
co_result_t co_consensus_evaluate(
    const co_vote_t *votes,
    size_t vote_count,
    uint32_t expected_epoch,
    uint32_t quorum,
    co_consensus_result_t *result);

#ifdef __cplusplus
}
#endif

#endif
