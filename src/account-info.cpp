#include "account-info.h"

AccountInfo::AccountInfo(const std::string &id, AccountType type)
    : id_(id)
    , type_(type)
{}

const std::string &AccountInfo::getId() const
{
    return id_;
}

AccountType AccountInfo::getType() const
{
    return type_;
}