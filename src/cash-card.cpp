#include "cash-card.h"

BEGIN_ATM_MACHINE

CashCard::CashCard(const std::string &id)
    : id_(id)
{
}

const std::string &CashCard::getId() const
{
    return id_;
}

END_ATM_MACHINE
