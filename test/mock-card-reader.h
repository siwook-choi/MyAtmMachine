#ifndef MOCK_CARD_READER_H_
#define MOCK_CARD_READER_H_

#include "atm-machine-global.h"
#include "card-reader.h"
#include "gmock/gmock.h"

BEGIN_ATM_MACHINE

class MockCardReader : public CardReader
{
public:
    MOCK_METHOD(bool, hasCard, (), (override));
    MOCK_METHOD(OperationResult, readCard, (CashCard &), (override));
    MOCK_METHOD(OperationResult, ejectCard, (), (override));
};

END_ATM_MACHINE

#endif  // MOCK_CARD_READER_H_
