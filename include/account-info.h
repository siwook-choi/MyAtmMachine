#ifndef ACCOUNT_INFO_H_
#define ACCOUNT_INFO_H_

#include <string>

enum class AccountType {
    Unspecified,
    Savings,
    Checking,
    Credit
};

class AccountInfo {
public:
    AccountInfo(const std::string &id = "", AccountType type = AccountType::Unspecified);

    const std::string &getId() const;
    AccountType getType() const;

private:
    std::string id_;
    AccountType type_;
};

#endif  // ACCOUNT_H_
