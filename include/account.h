#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <string>

enum class AccountType {
    Savings,
    Checking,
    Credit
};

class Account {
private:
    std::string id_;
    AccountType type_;
};

#endif  // ACCOUNT_H_
