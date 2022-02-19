#ifndef BANK_SERVER_H_
#define BANK_SERVER_H_

#include "atm-machine-global.h"
#include "cash-card.h"
#include "pin-number.h"
#include "account.h"
#include "operation-result.h"

BEGIN_ATM_MACHINE

/**
 * @brief Interface of a bank server for the ATM machine.
 */
class BankServer
{
public:
    BankServer() = default;
    virtual ~BankServer() = default;

    /**
     * @brief Authenticate the cash card with the pin number.
     * @param cashCard
     * @param pinNumber
     * @return OperationResult 
     */
    virtual OperationResult authenticate(const CashCard &cashCard, const PinNumber &pinNumber) = 0;
    virtual OperationResult selectAccount(
        const CashCard &cashCard,
        const PinNumber &pinNumber,
        AccountType type,
        AccountSession &session) = 0;

    /**
     * @brief Get information of an account.
     * @param session Valid session of the account.
     * @param[out] info Information of the account.
     * @return OperationResult 
     */
    virtual OperationResult seeBalance(const AccountSession &session, AccountInfo &info) = 0;

    /**
     * @brief Withdraw money from an account.
     * @param session Valid session of the account.
     * @param amount Amount of money to withdraw.
     * @return OperationResult 
     */
    virtual OperationResult withdraw(const AccountSession &session, unsigned int amount) = 0;

    /**
     * @brief Deposit money to an account
     * @param session Valid session of the account.
     * @param amount Amount of money to deposit.
     * @return OperationResult 
     */
    virtual OperationResult deposit(const AccountSession &session, unsigned int amount) = 0;
};

END_ATM_MACHINE

#endif  // BANK_SERVER_H_
