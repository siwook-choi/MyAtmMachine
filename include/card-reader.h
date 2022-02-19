#ifndef CARD_READER_H_
#define CARD_READER_H_

#include "atm-machine-global.h"
#include "operation-result.h"
#include "cash-card.h"

BEGIN_ATM_MACHINE

/**
 * @brief Interface of a card reader for the ATM machine.
 */
class CardReader
{
public:
    CardReader() = default;
    virtual ~CardReader() = default;

    /**
     * @brief Check if card reader has a card.
     * @return true if card reader has a card; false otherwise.
     */
    virtual bool hasCard() = 0;

    /**
     * @brief Read the inserted cash card.
     * @param[out] cashCard Cash card instance read.
     * @return OperationResult 
     */
    virtual OperationResult readCard(CashCard &cashCard) = 0;

    /**
     * @brief Eject the inserted cash card.
     * @return OperationResult 
     */
    virtual OperationResult ejectCard() = 0;
};

END_ATM_MACHINE

#endif  // CARD_READER_H_
