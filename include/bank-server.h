#ifndef BANK_SERVER_H_
#define BANK_SERVER_H_

#include "atm-machine-global.h"
#include "cash-card.h"
#include "pin-number.h"
#include "account.h"
#include "operation-result.h"

BEGIN_ATM_MACHINE

class BankServer
{
public:
    BankServer() = default;
    virtual ~BankServer() = default;

    virtual OperationResult authenticate(const CashCard &cashCard, const PinNumber &pinNumber) = 0;
    virtual OperationResult selectAccount(
        const CashCard &cashCard,
        const PinNumber &pinNumber,
        AccountType type,
        AccountSession &session) = 0;

    virtual OperationResult seeBalance(const AccountSession &session, AccountInfo &info) = 0;
    virtual OperationResult withdraw(const AccountSession &session, unsigned int amount) = 0;
    virtual OperationResult deposit(const AccountSession &session, unsigned int amount) = 0;
};

END_ATM_MACHINE

#endif  // BANK_SERVER_H_
