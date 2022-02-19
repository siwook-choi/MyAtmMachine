#ifndef CASH_BIN_H_
#define CASH_BIN_H_

#include "atm-machine-global.h"

BEGIN_ATM_MACHINE

/**
 * @brief Interface of a cash bin for the ATM Machine.
 */
class CashBin
{
public:
    CashBin() = default;
    virtual ~CashBin() = default;

    /**
     * @brief Set the amount of cash in CashBin.
     * @param amount Amount of cash.
     */
    virtual void setAmountCash(unsigned int amount) = 0;

    /**
     * @brief Get the amount of cash in CashBin.
     * @return Amount of cash in CashBin.
     */
    virtual unsigned int getAmountCash() = 0;

    /**
     * @brief Dispense cash from CashBin.
     * @param amount Amount of cash to dispense.
     * @return OperationResult 
     */
    virtual OperationResult dispenseCash(unsigned int amount) = 0;

    /**
     * @brief Count amount of cash in cash tray.
     * @param[out] amount Amount of cash in cash tray.
     * @return OperationResult 
     */
    virtual OperationResult countCash(unsigned int &amount) = 0;
};

END_ATM_MACHINE

#endif // CASH_BIN_H_
