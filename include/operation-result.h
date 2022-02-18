#ifndef OPERATION_RESULT_H_
#define OPERATION_RESULT_H_

#include "atm-machine-global.h"

#include <string>

BEGIN_ATM_MACHINE

enum class ErrorCode
{
    Ok=0,
    InvalidOperation,
    TransactionFailed,
    AuthenticationFailed,
    OutOfCash,
    CashBinFailure,
    UnknownError
};

class OperationResult
{
public:
    explicit OperationResult(ErrorCode code = ErrorCode::Ok, const std::string &message = "");

    bool isSucceed() const;
    bool isFatal() const;
    ErrorCode getCode() const;
    const std::string &getMessage() const;

private:
    ErrorCode code_;
    std::string message_;
};

END_ATM_MACHINE

#endif  // OPERATION_RESULT_H_
