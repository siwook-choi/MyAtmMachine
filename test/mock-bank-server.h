#ifndef MOCK_BANK_SERVER_H_
#define MOCK_BANK_SERVER_H_

#include "bank-server.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <memory>

class MockBankServer : public BankServer
{
public:
    MOCK_METHOD(OperationResult, authenticate, (const CashCard &, const PinNumber &), (override));
    MOCK_METHOD(OperationResult, selectAccount, (const CashCard &, const PinNumber &, AccountType,  AccountSession &), (override));
    MOCK_METHOD(OperationResult, seeBalance, (const AccountSession &, AccountInfo &), (override));
    MOCK_METHOD(OperationResult, withdraw, (const AccountSession &, unsigned int), (override));
    MOCK_METHOD(OperationResult, deposit, (const AccountSession &, unsigned int), (override));
};

#endif  // MOCK_BANK_SERVER_H_
