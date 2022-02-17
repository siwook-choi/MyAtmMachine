#ifndef PIN_H_
#define PIN_H_

#include <string>
#include <stdexcept>

class PinNumber
{
public:
    explicit PinNumber(const std::string &pin="0000");

    const std::string &toString() const;

private:
    const std::string pin_;
};

#endif  // PIN_H_
