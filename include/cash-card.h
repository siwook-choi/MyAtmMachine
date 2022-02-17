#ifndef CASH_CARD_H_
#define CASH_CARD_H_

#include <string>

class CashCard
{
public:
    explicit CashCard(const std::string &cardId = "");
    const std::string &getCardId() const;
    
private:
    std::string cardId_;
};

#endif  // CASH_CARD_H_
