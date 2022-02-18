#ifndef CARD_READER_H_
#define CARD_READER_H_

#include "operation-result.h"
#include "cash-card.h"

class CardReader
{
public:
    CardReader() = default;
    virtual ~CardReader() = default;

    virtual bool hasCard() = 0;
    virtual OperationResult readCard(CashCard &cashCard) const = 0;
    virtual OperationResult ejectCard() = 0;
};

#endif  // CARD_READER_H_
