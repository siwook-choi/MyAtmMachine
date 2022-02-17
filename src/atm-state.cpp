#include "atm-state.h"

FSM_INITIAL_STATE(AtmState, IdleState)

void IdleState::react(const CardInserted &event)
{
    transit<ReadingCardState>();
}

void ReadingCardState::react(const ErrorOccured &event)
{
}

void ReadingCardState::react(const CardVerified &event)
{
}
