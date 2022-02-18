#include "account.h"

BEGIN_ATM_MACHINE

AccountId::AccountId(const std::string &id)
    : id_(id)
{}

const std::string &AccountId::toString() const
{
    return id_;
}


AccountSession::AccountSession(
    const AccountId &id,
    std::string key)
    : id_(id)
    , key_(key)
{}

const AccountId &AccountSession::getId() const
{
    return id_;
}

const std::string &AccountSession::getKey() const
{
    return key_;
}

AccountInfo::AccountInfo(const AccountId &id, AccountType type, unsigned int balance)
    : id_(id)
    , type_(type)
    , balance_(balance)
{}

const AccountId &AccountInfo::getId() const
{
    return id_;
}

AccountType AccountInfo::getType() const
{
    return type_;
}

unsigned int AccountInfo::getBalance() const
{
    return balance_;
}

END_ATM_MACHINE
