#ifndef MOCK_CASH_BIN_H_
#define MOCK_CASH_BIN_H_

#include "atm-machine-global.h"
#include "cash-bin.h"
#include "gmock/gmock.h"

BEGIN_ATM_MACHINE

class MockCashBin : public CashBin
{
public:
    MOCK_METHOD(void, setAmountCash, (unsigned int), (override));
    MOCK_METHOD(unsigned int, getAmountCash, (), (override));
    MOCK_METHOD(OperationResult, dispenseCash, (unsigned int), (override));
};

END_ATM_MACHINE

#endif  // MOCK_CASH_BIN_H_
