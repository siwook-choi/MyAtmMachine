#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "atm-machine-global.h"
#include "atm-machine.h"
#include "atm-state.h"
#include "mock-bank-server.h"
#include "mock-card-reader.h"
#include "mock-cash-bin.h"

#include <memory>

USING_ATM_MACHINE
using namespace testing;

TEST(TestAtmState, TestAtmState)
{   
    auto bankServer = std::make_shared<MockBankServer>();
    auto cashBin = std::make_shared<MockCashBin>();
    auto cardReader = std::make_shared<MockCardReader>();
    
    EXPECT_CALL((*cardReader), hasCard())
        .WillRepeatedly(Return(true));

    EXPECT_CALL((*cardReader), readCard(_))
        .WillRepeatedly(Return(OperationResult()));

    EXPECT_CALL((*cardReader), ejectCard())
        .WillRepeatedly(Return(OperationResult()));
    
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

    AtmState::dispatch(TransactionFinished());
    EXPECT_TRUE(AtmState::is_in_state<ChoosingTransactionState>());

    AtmState::dispatch(Canceled());
    EXPECT_TRUE(AtmState::is_in_state<EjectingCardState>());

    AtmState::dispatch(CardPulledOut());
    EXPECT_TRUE(AtmState::is_in_state<IdleState>());

    AtmMachine::release();
}