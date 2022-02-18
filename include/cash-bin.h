#ifndef CASH_BIN_H_
#define CASH_BIN_H_

class CashBin
{
public:
    CashBin() = default;
    virtual ~CashBin() = default;

    virtual void setAmountCash(unsigned int amount) = 0;
    virtual unsigned int getAmountCash() = 0;

    virtual OperationResult withdrawCash(unsigned int amount) = 0;
};

#endif // CASH_BIN_H_
