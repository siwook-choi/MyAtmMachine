#include "operation-result.h"

OperationResult::OperationResult(int code, const std::string &message)
    : code_(code)
    , message_(message)
{
}

bool OperationResult::isSucceed() const
{
    return code_ == 0;
}

int OperationResult::getCode() const
{
    return code_;
}

const std::string &OperationResult::getMessage() const
{
    return message_;
}