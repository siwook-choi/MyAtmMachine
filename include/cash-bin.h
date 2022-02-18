#ifndef CASH_BIN_H_
#define CASH_BIN_H_

#include "atm-machine-global.h"

BEGIN_ATM_MACHINE

class CashBin
{
public:
    CashBin() = default;
    virtual ~CashBin() = default;

    virtual void setAmountCash(unsigned int amount) = 0;
    virtual unsigned int getAmountCash() = 0;

    virtual OperationResult dispenseCash(unsigned int amount) = 0;
};

END_ATM_MACHINE

#endif // CASH_BIN_H_
