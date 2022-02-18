#ifndef ATM_STATE_H_
#define ATM_STATE_H_

#include "atm-event.h"
#include "tinyfsm.hpp"
#include "operation-result.h"
#include "cash-card.h"
#include "pin-number.h"
#include "account.h"
#include "atm-state-enum.h"
#include "bank-server.h"
#include "cash-bin.h"
#include "card-reader.h"


#include <functional>
#include <memory>
#include <stdexcept>

class AtmState : public tinyfsm::MooreMachine<AtmState>
{
public:
    virtual AtmStateEnum getState() const = 0;

    virtual void entry()
    {
        stateCallback_(getState());
    }

    void react(const tinyfsm::Event &event) {
        throw std::runtime_error("Unhandled event in AtmState");
    };

    virtual void react(const Initialized &event) { };
    virtual void react(const Canceled &event) { };
    virtual void react(const ErrorOccured &event) { };
    virtual void react(const CardInserted &event) { };
    virtual void react(const CardRead &event) { };
    virtual void react(const CardPulledOut &event) { };
    virtual void react(const Authenticated &event) { };
    virtual void react(const AccountSelected &event) { };
    virtual void react(const TransactionChosen &event) { };
    virtual void react(const TransactionContinued &event) { };
    virtual void react(const TransactionFinished &event) { };
    virtual void react(const CashRefilled &event) { };

    virtual OperationResult initialize(
        std::shared_ptr<BankServer> bankServer,
        std::shared_ptr<CashBin> cashBin,
        std::shared_ptr<CardReader> cardReader)
    {
        return OperationResult(ErrorCode::InvalidOperation, "Invalid Operation");
    }

    virtual OperationResult enterPin(const PinNumber &pinNumber)
    {
        return OperationResult(ErrorCode::InvalidOperation, "Invalid Operation");
    }

    virtual OperationResult selectAccount(AccountType accountType)
    {
        return OperationResult(ErrorCode::InvalidOperation, "Invalid Operation");
    }

    virtual OperationResult seeBalance(AccountInfo &accountInfo)
    {
        accountInfo = AccountInfo();
        return OperationResult(ErrorCode::InvalidOperation, "Invalid Operation");
    }

    virtual OperationResult deposit(unsigned int amount)
    {
        return OperationResult(ErrorCode::InvalidOperation, "Invalid Operation");
    }

    virtual OperationResult withdraw(unsigned int amount)
    {
        return OperationResult(ErrorCode::InvalidOperation, "Invalid Operation");
    }

    virtual OperationResult release();

    static void setStateCallback(std::function<void(AtmStateEnum)> stateCallback)
    {
        stateCallback_ = stateCallback;
    }

protected:
    static std::function<void(AtmStateEnum)> stateCallback_;
    static std::shared_ptr<BankServer> bankServer_;
    static std::shared_ptr<CashBin> cashBin_;
    static std::shared_ptr<CardReader> cardReader_;
    static CashCard cashCard_;
    static PinNumber pinNumber_;
    static AccountSession accountSession_;
};

class InitializingState : public AtmState
{
    AtmStateEnum getState() const override;
    void react(const Initialized &event) override;

    OperationResult initialize(
        std::shared_ptr<BankServer> bankServer,
        std::shared_ptr<CashBin> cashBin,
        std::shared_ptr<CardReader> cardReader) override;
};

class IdleState : public AtmState
{
public:
    AtmStateEnum getState() const override;
    void react(const ErrorOccured &event) override;
    void react(const CardInserted &event) override;
};

class ReadingCardState : public AtmState
{
public:
    AtmStateEnum getState() const override;
    void react(const ErrorOccured &event) override;
    void react(const CardRead &event) override;

    void entry() override;
};

class AuthenticatingState : public AtmState
{
public:
    AtmStateEnum getState() const override;
    void react(const Canceled &event) override;
    void react(const ErrorOccured &event) override;
    void react(const Authenticated &event) override;

    OperationResult enterPin(const PinNumber &pinNumber);
};

class SelectingAccountState : public AtmState
{
public:
    AtmStateEnum getState() const override;
    void react(const Canceled &event) override;
    void react(const ErrorOccured &event) override;
    void react(const AccountSelected &event) override;

    OperationResult selectAccount(AccountType accountType);
};

class ChoosingTransactionState : public AtmState
{
public:
    AtmStateEnum getState() const override;
    void react(const Canceled &event) override;
    void react(const ErrorOccured &event) override;
    void react(const TransactionChosen &event) override;
};

class PerformingTransactionState : public AtmState
{
public:
    AtmStateEnum getState() const override;
    void react(const Canceled &event) override;
    void react(const ErrorOccured &event) override;
    void react(const TransactionContinued &event) override;
    void react(const TransactionFinished &event) override;
};

class EjectingCardState : public AtmState
{
public:
    AtmStateEnum getState() const override;
    void react(const CardPulledOut &event) override;

    void entry() override;
};

class OutOfCashState : public AtmState
{
public:
    AtmStateEnum getState() const override;
    void react(const CashRefilled &event) override;

    void entry() override;
};

class OutOfOrderState : public AtmState
{
public:
    AtmStateEnum getState() const override;

    void entry() override;
};

#endif  // ATM_STATE_H_
