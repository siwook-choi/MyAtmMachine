#include <gtest/gtest.h>
#include <memory>
#include "atm-state.h"

TEST(TestAtmState, TestAtmWithdrawlState)
{
    AtmState::start();
    EXPECT_TRUE(AtmState::is_in_state<IdleState>());

    AtmState::dispatch(CardInserted());
    EXPECT_TRUE(AtmState::is_in_state<ReadingCardState>());

    AtmState::dispatch(CardVerified());
    EXPECT_TRUE(AtmState::is_in_state<ReadingPinState>());

    AtmState::dispatch(PinVerified());
    EXPECT_TRUE(AtmState::is_in_state<SelectingAccountState>());

    AtmState::dispatch(AccountSelected());
    EXPECT_TRUE(AtmState::is_in_state<ChoosingTransactionState>());

    AtmState::dispatch(TransactionChosen());
    EXPECT_TRUE(AtmState::is_in_state<PerformingTransactionState>());

    AtmState::dispatch(TransactionContinued());
    EXPECT_TRUE(AtmState::is_in_state<ChoosingTransactionState>());

    AtmState::dispatch(TransactionChosen());
    EXPECT_TRUE(AtmState::is_in_state<PerformingTransactionState>());

    AtmState::dispatch(TransactionFinished());
    EXPECT_TRUE(AtmState::is_in_state<EjectingCardState>());

    AtmState::dispatch(CardEjected());
    EXPECT_TRUE(AtmState::is_in_state<IdleState>());
}