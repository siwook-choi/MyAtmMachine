#include "cash-card.h"

BEGIN_ATM_MACHINE

CashCard::CashCard(const std::string &cardId)
    : cardId_(cardId)
{
}

const std::string &CashCard::getCardId() const
{
    return cardId_;
}

END_ATM_MACHINE
