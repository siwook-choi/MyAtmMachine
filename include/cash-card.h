#ifndef CASH_CARD_H_
#define CASH_CARD_H_

#include "atm-machine-global.h"

#include <string>

BEGIN_ATM_MACHINE

class CashCard
{
public:
    explicit CashCard(const std::string &id = "");
    const std::string &getId() const;
    
private:
    std::string id_;
};

END_ATM_MACHINE

#endif  // CASH_CARD_H_
