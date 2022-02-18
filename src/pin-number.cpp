#include "pin-number.h"
#include <stdexcept>

BEGIN_ATM_MACHINE

PinNumber::PinNumber(const std::string &pin)
    : pin_(pin)
{
    if (pin_.size() != 4) {
        std::string errmsg("Invalid PIN number. Length of PIN number should be 4: PIN(");
        errmsg += pin_;
        errmsg += ')';
        throw std::invalid_argument(errmsg);
    }

    for (const auto digit: pin_) {
        if (!std::isdigit(digit)) {
            std::string errmsg("Invalid PIN number. PIN number should only contain digits: PIN(");
            errmsg += pin_;
            errmsg += ')';
            throw std::invalid_argument(errmsg);
        }
    }
}

const std::string &PinNumber::toString() const
{
    return pin_;
}

END_ATM_MACHINE
