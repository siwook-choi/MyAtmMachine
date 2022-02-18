#ifndef ATM_MACHINE_H_
#define ATM_MACHINE_H_

#include "bank-server.h"
#include "cash-bin.h"
#include "card-reader.h"

#include "cash-card.h"
#include "pin-number.h"
#include "account.h"
#include "operation-result.h"
#include "atm-state-enum.h"

#include <functional>
#include <memory>

class AtmMachine
{
public:
    AtmMachine() = default;

    /**
     * @brief Get the State of ATM machine.
     * @return AtmStateEnum 
     */
    static AtmStateEnum getState();
    
    /**
     * @brief Initialize ATM machine.
     * Only available when ATM is in InitializingState.
     * @param bankServer Pointer to BankServer
     * @param cashBin Pointer to CashBin
     * @param cardReader Pointer to CardReader
     * @return OperationResult 
     */
    static OperationResult initialize(
        std::shared_ptr<BankServer> bankServer,
        std::shared_ptr<CashBin> cashBin,
        std::shared_ptr<CardReader> cardReader);

    /**
     * @brief Enter PIN number.
     * Only available when ATM is in ReadingPinState.
     * @param pinNumber PIN number instance.
     * @return OperationResult 
     */
    static OperationResult enterPin(const PinNumber &pinNumber);

    /**
     * @brief Select account type.
     * Only available when ATM is in SelectingAccountState.
     * @param accountType Type of account.
     * @return OperationResult 
     */
    static OperationResult selectAccount(AccountType accountType);

    static OperationResult seeBalance(AccountInfo &accountInfo);
    static OperationResult deposit(unsigned int amount);
    static OperationResult withdraw(unsigned int amount);

    /**
     * @brief Cancel current operation.
     * 
     * @return OperationResult 
     */
    static OperationResult cancel();
    
    static void setStateCallback(std::function<void(AtmStateEnum)> stateCallback);
};

#endif  // ATM_MACHINE_H_