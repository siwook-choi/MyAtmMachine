#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "atm-machine.h"
#include "atm-state.h"
#include "mock-bank-server.h"
#include "mock-card-reader.h"
#include "mock-cash-bin.h"

#include <memory>

using namespace testing;

TEST(TestAtmMachine, TestAtmWithdrawl)
{   
    auto bankServer = std::make_shared<MockBankServer>();
    auto cashBin = std::make_shared<MockCashBin>();
    auto cardReader = std::make_shared<MockCardReader>();
    
    ON_CALL((*cardReader), hasCard())
        .WillByDefault(Return(true));

    ON_CALL((*cardReader), readCard(_))
        .WillByDefault(Return(OperationResult()));

    ON_CALL((*cardReader), ejectCard())
        .WillByDefault(Return(OperationResult()));
    
    AtmMachine::initialize(bankServer, cashBin, cardReader);
    EXPECT_TRUE(AtmState::is_in_state<IdleState>());
    
    AtmState::dispatch(CardInserted());
    EXPECT_TRUE(AtmState::is_in_state<AuthenticatingState>());

    AtmState::dispatch(Authenticated());
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

    AtmState::dispatch(CardPulledOut());
    EXPECT_TRUE(AtmState::is_in_state<IdleState>());

    AtmMachine::release();
}