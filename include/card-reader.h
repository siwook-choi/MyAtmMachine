#ifndef CARD_READER_H_
#define CARD_READER_H_

#include "atm-machine-global.h"
#include "operation-result.h"
#include "cash-card.h"

BEGIN_ATM_MACHINE

class CardReader
{
public:
    CardReader() = default;
    virtual ~CardReader() = default;

    virtual bool hasCard() = 0;
    virtual OperationResult readCard(CashCard &cashCard) = 0;
    virtual OperationResult ejectCard() = 0;
};

END_ATM_MACHINE

#endif  // CARD_READER_H_
