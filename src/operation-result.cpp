#include "operation-result.h"

BEGIN_ATM_MACHINE

OperationResult::OperationResult(ErrorCode code, const std::string &message)
    : code_(code)
    , message_(message)
{
}

bool OperationResult::isSucceed() const
{
    return code_ == ErrorCode::Ok;
}

bool OperationResult::isFatal() const
{
    if (code_ == ErrorCode::CashBinFailure || code_ == ErrorCode::UnknownError)
        return true;

    return false;
}

ErrorCode OperationResult::getCode() const
{
    return code_;
}

const std::string &OperationResult::getMessage() const
{
    return message_;
}

END_ATM_MACHINE
