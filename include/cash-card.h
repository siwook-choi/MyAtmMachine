#ifndef CASH_CARD_H_
#define CASH_CARD_H_

#include "atm-machine-global.h"

#include <string>

BEGIN_ATM_MACHINE

class CashCard
{
public:
    explicit CashCard(const std::string &cardId = "");
    const std::string &getCardId() const;
    
private:
    std::string cardId_;
};

END_ATM_MACHINE

#endif  // CASH_CARD_H_
