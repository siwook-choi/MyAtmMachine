#ifndef ATM_MACHINE_H_
#define ATM_MACHINE_H_

#include "atm-machine-global.h"

#include "bank-server.h"
#include "cash-bin.h"
#include "card-reader.h"

#include "pin-number.h"
#include "account.h"
#include "operation-result.h"
#include "atm-state-enum.h"

#include <functional>
#include <memory>

BEGIN_ATM_MACHINE

/**
 * @brief AtmMachine is a controller for a ATM machine.
 */
class AtmMachine
{
public:
    AtmMachine() = delete;
    
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
     * @brief Release resources and set AtmState to InitializingState.
     * @return OperationResult 
     */
    static OperationResult release();

    /**
     * @brief Get the State of ATM machine.
     * @return AtmStateEnum 
     */
    static AtmStateEnum getState();

    /**
     * @brief Enter PIN number.
     * Available when ATM is in ReadingPinState.
     * @param pinNumber PIN number instance.
     * @return OperationResult 
     */
    static OperationResult enterPin(const PinNumber &pinNumber);

    /**
     * @brief Select account type.
     * Available when ATM is in SelectingAccountState.
     * @param accountType Type of account.
     * @return OperationResult 
     */
    static OperationResult selectAccount(AccountType accountType);

    /**
     * @brief See balance of current account.
     * Available when ATM is in ChoosingTransactionState.
     * @param[out] accountInfo Information of current account. 
     * @return OperationResult 
     */
    static OperationResult seeBalance(AccountInfo &accountInfo);

    /**
     * @brief Deposit cash to current account.
     * Available when ATM is in ChoosingTransactionState.
     * @return OperationResult 
     */
    static OperationResult deposit();

    /**
     * @brief Withdraw cash from current account.
     * Available when ATM is in ChoosingTransactionState.
     * @param amount Amount of money to withdraw
     * @return OperationResult 
     */
    static OperationResult withdraw(unsigned int amount);

    /**
     * @brief Cancel current operation.
     * Available when ATM is in AuthenticatingState, SelectingAccountState, and ChoosingTransactionState.
     * @return OperationResult 
     */
    static OperationResult cancel();
    
    /**
     * @brief Set the callback function for state change.
     * @param stateCallback Callback function called when AtmState changes.
     */
    static void setStateCallback(std::function<void(AtmStateEnum)> stateCallback);
};

END_ATM_MACHINE

#endif  // ATM_MACHINE_H_