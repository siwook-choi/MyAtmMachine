#ifndef ATM_MACHINE_H_
#define ATM_MACHINE_H_

#include "cash-card.h"
#include "pin-number.h"
#include "cash-bin.h"
#include "account.h"
#include "operation-result.h"

class AtmMachineOperations
{
    AtmMachineOperations() = default;
    virtual ~AtmMachineOperations() = default;

    virtual OperationResult insertCard(const CashCard &card) = 0;
    virtual OperationResult ejectCard() = 0;
    virtual OperationResult enterPin(const PinNumber &pin) = 0;
    virtual OperationResult selectAccount(AccountType type) = 0;

    virtual OperationResult seeBalance() = 0;
    virtual OperationResult deposit(unsigned int amount) = 0;
    virtual OperationResult withdraw(unsigned int amount) = 0;
};

class AtmMachine : AtmMachineOperations
{
public:
    AtmMachine() = default;
    virtual ~AtmMachine() = default;
};

#endif  // ATM_MACHINE_H_