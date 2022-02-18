#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "atm-machine.h"
#include "atm-state.h"
#include "mock-bank-server.h"
#include "mock-card-reader.h"
#include "mock-cash-bin.h"

#include <memory>

using namespace testing;

TEST(TestAtmMachine, TestAtmWithdrawal)
{
    const auto AmountMoney = 1000U;

    auto bankServer = std::make_shared<MockBankServer>();
    auto cashBin = std::make_shared<MockCashBin>();
    auto cardReader = std::make_shared<MockCardReader>();
    
    EXPECT_CALL((*bankServer), authenticate(_,_))
        .Times(1)
        .WillRepeatedly(Return(OperationResult()));
    EXPECT_CALL((*bankServer), selectAccount(_,_,_,_))
        .Times(1)
        .WillRepeatedly(Return(OperationResult()));
    EXPECT_CALL((*bankServer), withdraw(_,AmountMoney))
        .Times(1)
        .WillRepeatedly(Return(OperationResult()));
    EXPECT_CALL((*cashBin), withdrawCash(AmountMoney))
        .Times(1)
        .WillRepeatedly(Return(OperationResult()));
    EXPECT_CALL((*cashBin), getAmountCash())
        .Times(1)
        .WillRepeatedly(Return(AmountMoney));

    EXPECT_CALL((*cardReader), hasCard())
        .WillRepeatedly(Return(true));

    EXPECT_CALL((*cardReader), readCard(_))
        .WillRepeatedly(Return(OperationResult()));

    EXPECT_CALL((*cardReader), ejectCard())
        .WillRepeatedly(Return(OperationResult()));

    EXPECT_TRUE(AtmMachine::initialize(bankServer, cashBin, cardReader).isSucceed());
    
    AtmState::dispatch(CardInserted());
    
    EXPECT_TRUE(AtmMachine::enterPin(PinNumber("1111")).isSucceed());
    EXPECT_TRUE(AtmMachine::selectAccount(AccountType::Checking).isSucceed());
    EXPECT_TRUE(AtmMachine::withdraw(AmountMoney).isSucceed());
    EXPECT_TRUE(AtmMachine::cancel().isSucceed());
    EXPECT_TRUE(AtmMachine::release().isSucceed());
}