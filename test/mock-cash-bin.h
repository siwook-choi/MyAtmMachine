#ifndef MOCK_CASH_BIN_H_
#define MOCK_CASH_BIN_H_

#include "cash-bin.h"
#include "gmock/gmock.h"

class MockCashBin : public CashBin
{
public:
    MOCK_METHOD(void, setAmountCash, (unsigned int), (override));
    MOCK_METHOD(unsigned int, getAmountCash, (), (override));
    MOCK_METHOD(OperationResult, withdrawCash, (unsigned int), (override));
};

#endif  // MOCK_CASH_BIN_H_
