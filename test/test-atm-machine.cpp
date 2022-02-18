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

TEST(TestAtmMachine, TestAtmWithdrawal)
{
    const auto amountMoney = 1000U;

    auto bankServer = std::make_shared<MockBankServer>();
    auto cashBin = std::make_shared<MockCashBin>();
    auto cardReader = std::make_shared<MockCardReader>();
    
    EXPECT_CALL((*bankServer), authenticate(_,_))
        .Times(1)
        .WillRepeatedly(Return(OperationResult()));
    EXPECT_CALL((*bankServer), selectAccount(_,_,_,_))
        .Times(1)
        .WillRepeatedly(Return(OperationResult()));
    EXPECT_CALL((*bankServer), withdraw(_,amountMoney))
        .Times(1)
        .WillRepeatedly(Return(OperationResult()));
    EXPECT_CALL((*cashBin), dispenseCash(amountMoney))
        .Times(1)
        .WillRepeatedly(Return(OperationResult()));
    EXPECT_CALL((*cashBin), getAmountCash())
        .Times(1)
        .WillRepeatedly(Return(amountMoney));

    EXPECT_CALL((*cardReader), hasCard())
        .WillRepeatedly(Return(true));

    EXPECT_CALL((*cardReader), readCard(_))
        .WillRepeatedly(Return(OperationResult()));

    EXPECT_CALL((*cardReader), ejectCard())
        .WillRepeatedly(Return(OperationResult()));
    
    {
        EXPECT_TRUE(AtmMachine::initialize(bankServer, cashBin, cardReader).isSucceed());
        AtmState::dispatch(CardInserted());
        
        EXPECT_TRUE(AtmMachine::enterPin(PinNumber("1111")).isSucceed());
        EXPECT_TRUE(AtmMachine::selectAccount(AccountType::Checking).isSucceed());
        EXPECT_TRUE(AtmMachine::withdraw(amountMoney).isSucceed());
        EXPECT_TRUE(AtmMachine::cancel().isSucceed());
        EXPECT_TRUE(AtmMachine::release().isSucceed());
    }
}

TEST(TestAtmMachine, TestAtmSeeBalance)
{
    const auto expectedAccountId = AccountId("account_id");
    const auto expectedAccountKey = std::string("account_key");
    const auto expectedAccountType = AccountType::Savings;
    const auto expectedBalance = 1000U;
    
    const auto expectedAccountSession = AccountSession(expectedAccountId, expectedAccountKey);
    const auto expectedAccountInfo = AccountInfo(expectedAccountId, expectedAccountType, expectedBalance);

    auto bankServer = std::make_shared<MockBankServer>();
    auto cashBin = std::make_shared<MockCashBin>();
    auto cardReader = std::make_shared<MockCardReader>();
    
    EXPECT_CALL((*bankServer), authenticate(_,_))
        .Times(1)
        .WillRepeatedly(Return(OperationResult()));
    EXPECT_CALL((*bankServer), selectAccount(_,_,_,_))
        .Times(1)
        .WillRepeatedly(DoAll(SetArgReferee<3>(expectedAccountSession), Return(OperationResult())));
    EXPECT_CALL((*bankServer), seeBalance(_,_))
        .Times(1)
        .WillRepeatedly(DoAll(SetArgReferee<1>(expectedAccountInfo), Return(OperationResult())));

    EXPECT_CALL((*cardReader), hasCard())
        .WillRepeatedly(Return(true));

    EXPECT_CALL((*cardReader), readCard(_))
        .WillRepeatedly(Return(OperationResult()));

    EXPECT_CALL((*cardReader), ejectCard())
        .WillRepeatedly(Return(OperationResult()));
    
    {
        EXPECT_TRUE(AtmMachine::initialize(bankServer, cashBin, cardReader).isSucceed());
        AtmState::dispatch(CardInserted());
        
        EXPECT_TRUE(AtmMachine::enterPin(PinNumber("1111")).isSucceed());
        EXPECT_TRUE(AtmMachine::selectAccount(AccountType::Checking).isSucceed());

        AccountInfo accountInfo;
        EXPECT_TRUE(AtmMachine::seeBalance(accountInfo).isSucceed());
        EXPECT_TRUE(AtmMachine::cancel().isSucceed());
        EXPECT_TRUE(AtmMachine::release().isSucceed());

        EXPECT_EQ(accountInfo.getId().toString(), expectedAccountInfo.getId().toString());
        EXPECT_EQ(accountInfo.getType(), expectedAccountInfo.getType());
        EXPECT_EQ(accountInfo.getBalance(), expectedAccountInfo.getBalance());
    }
}

TEST(TestAtmMachine, TestAtmDeposit)
{
    const auto amountMoney = 1000U;

    auto bankServer = std::make_shared<MockBankServer>();
    auto cashBin = std::make_shared<MockCashBin>();
    auto cardReader = std::make_shared<MockCardReader>();
    
    EXPECT_CALL((*bankServer), authenticate(_,_))
        .Times(1)
        .WillRepeatedly(Return(OperationResult()));
    EXPECT_CALL((*bankServer), selectAccount(_,_,_,_))
        .Times(1)
        .WillRepeatedly(Return(OperationResult()));
    EXPECT_CALL((*bankServer), deposit(_,amountMoney))
        .Times(1)
        .WillRepeatedly(Return(OperationResult()));

    EXPECT_CALL((*cashBin), countCash(_))
        .Times(1)
        .WillRepeatedly(DoAll(SetArgReferee<0>(amountMoney), Return(OperationResult())));

    EXPECT_CALL((*cardReader), hasCard())
        .WillRepeatedly(Return(true));

    EXPECT_CALL((*cardReader), readCard(_))
        .WillRepeatedly(Return(OperationResult()));

    EXPECT_CALL((*cardReader), ejectCard())
        .WillRepeatedly(Return(OperationResult()));
    
    {
        EXPECT_TRUE(AtmMachine::initialize(bankServer, cashBin, cardReader).isSucceed());
        AtmState::dispatch(CardInserted());
        
        EXPECT_TRUE(AtmMachine::enterPin(PinNumber("1111")).isSucceed());
        EXPECT_TRUE(AtmMachine::selectAccount(AccountType::Checking).isSucceed());
        EXPECT_TRUE(AtmMachine::deposit().isSucceed());
        EXPECT_TRUE(AtmMachine::cancel().isSucceed());
        EXPECT_TRUE(AtmMachine::release().isSucceed());
    }
}
