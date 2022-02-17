#include "cash-card.h"

CashCard::CashCard(const std::string &cardId)
    : cardId_(cardId)
{
}

const std::string &CashCard::getCardId() const
{
    return cardId_;
}
