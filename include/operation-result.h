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

/**
 * @brief Result of an operation.
 */
class OperationResult
{
public:
    explicit OperationResult(ErrorCode code = ErrorCode::Ok, const std::string &message = "");

    /**
     * @brief Check if operation has succeeded.
     * @return true if the operation succeeded; false otherwise.
     */
    bool isSucceed() const;

    /**
     * @brief Check if fatal error has occured.
     * @return true if fatal error has occured; false otherwise.
     */
    bool isFatal() const;

    /**
     * @brief Get the error code of the operation.
     * @return ErrorCode 
     */
    ErrorCode getCode() const;

    /**
     * @brief Get the message from the operation.
     * @return Message
     */
    const std::string &getMessage() const;

private:
    ErrorCode code_;
    std::string message_;
};

END_ATM_MACHINE

#endif  // OPERATION_RESULT_H_
