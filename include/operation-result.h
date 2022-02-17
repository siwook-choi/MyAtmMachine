#ifndef OPERATION_RESULT_H_
#define OPERATION_RESULT_H_

#include <string>

class OperationResult
{
public:
    explicit OperationResult(int code = 0, const std::string &message = "");

    bool isSucceed() const;
    int getCode() const;
    const std::string &getMessage() const;

private:
    int code_;
    std::string message_;
};

#endif  // OPERATION_RESULT_H_
