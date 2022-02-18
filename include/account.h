#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include "atm-machine-global.h"
#include <string>

BEGIN_ATM_MACHINE

enum class AccountType {
    Unspecified,
    Savings,
    Checking,
    Credit
};

class AccountId {
public:
    explicit AccountId(const std::string &id = "");

    const std::string &toString() const;

private:
    std::string id_;
};

class AccountSession {
public:
    explicit AccountSession(
        const AccountId &id = AccountId(),
        std::string key = "");

    const AccountId &getId() const;
    const std::string &getKey() const;

private:
    AccountId id_;
    std::string key_;
};

class AccountInfo {
public:
    AccountInfo(
        const AccountId &id = AccountId(),
        AccountType type = AccountType::Unspecified,
        unsigned int balance = 0U);

    const AccountId &getId() const;
    AccountType getType() const;
    unsigned int getBalance() const;

private:
    AccountId id_;
    AccountType type_;
    unsigned int balance_;
};

END_ATM_MACHINE

#endif  // ACCOUNT_H_
