#include "operation-result.h"

OperationResult::OperationResult(ErrorCode code, const std::string &message)
    : code_(code)
    , message_(message)
{
}

bool OperationResult::isSucceed() const
{
    return code_ == ErrorCode::Ok;
}

OperationResult::ErrorCode OperationResult::getCode() const
{
    return code_;
}

const std::string &OperationResult::getMessage() const
{
    return message_;
}