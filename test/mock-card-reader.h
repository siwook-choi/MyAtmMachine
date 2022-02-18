#ifndef MOCK_CARD_READER_H_
#define MOCK_CARD_READER_H_

#include "card-reader.h"
#include "gmock/gmock.h"

class MockCardReader : public CardReader
{
    MOCK_METHOD(bool, hasCard, (), (override));
    MOCK_METHOD(OperationResult, readCard, (CashCard &), (override));
    MOCK_METHOD(OperationResult, ejectCard, (), (override));
};

#endif  // MOCK_CARD_READER_H_
