#ifndef OPERATION_RESULT_H_
#define OPERATION_RESULT_H_

#include <string>

class OperationResult
{
public:
    enum class ErrorCode
    {
        Ok=0,
        InvalidOperation,
        TransactionFailed,
        OutOfCash,
        AuthenticationFailed
    };
    explicit OperationResult(ErrorCode code = ErrorCode::Ok, const std::string &message = "");

    bool isSucceed() const;
    ErrorCode getCode() const;
    const std::string &getMessage() const;

private:
    ErrorCode code_;
    std::string message_;
};

#endif  // OPERATION_RESULT_H_
