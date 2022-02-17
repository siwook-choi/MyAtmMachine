#ifndef BANK_SERVER_H_
#define BANK_SERVER_H_

#include "cash-card.h"
#include "pin-number.h"
#include "operation-result.h"

class BankServer
{
public:
    BankServer() = default;
    virtual ~BankServer() = default;

    virtual OperationResult verifyCard(const CashCard &cashCard) = 0;
    virtual OperationResult verifyPinNumber(const CashCard &cashCard, const PinNumber &pinNumber) = 0;
};

#endif  // BANK_SERVER_H_
