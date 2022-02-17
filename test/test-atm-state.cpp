#include <gtest/gtest.h>
#include <memory>
#include "atm-state.h"

TEST(TestAtmState, TestAtmWithdrawlState)
{
    AtmState atmState;
    AtmState::start();

    EXPECT_TRUE(atmState.is_in_state<IdleState>());
    atmState.react(CardInserted());
    EXPECT_TRUE(atmState.is_in_state<ReadingCardState>());
    atmState.react(CardVerified());
}