#ifndef ATM_STATE_H_
#define ATM_STATE_H_

#include "atm-event.h"
#include "tinyfsm.hpp"
#include "operation-result.h"
#include "cash-card.h"
#include "pin-number.h"
#include "cash-bin.h"
#include "account-info.h"
#include "bank-server.h"
#include "atm-state-enum.h"

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
    virtual void react(const CardEjected &event) { };
    virtual void react(const CardVerified &event) { };
    virtual void react(const PinVerified &event) { };
    virtual void react(const AccountSelected &event) { };
    virtual void react(const TransactionChosen &event) { };
    virtual void react(const TransactionContinued &event) { };
    virtual void react(const TransactionFinished &event) { };
    virtual void react(const CashRefilled &event) { };

    virtual OperationResult initialize(
        std::shared_ptr<BankServer> bankServer,
        std::shared_ptr<CashBin> cashBin)
    {
        return OperationResult(ErrorCode::InvalidOperation, "Invalid Operation");
    }

    virtual OperationResult insertCard(const CashCard &cashCard)
    {
        return OperationResult(ErrorCode::InvalidOperation, "Invalid Operation");
    }

    virtual OperationResult ejectCard()
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

    virtual OperationResult seeBalance()
    {
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

    static void setStateCallback(std::function<void(AtmStateEnum)> stateCallback)
    {
        stateCallback_ = stateCallback;
    }

protected:
    static std::function<void(AtmStateEnum)> stateCallback_;
    static std::shared_ptr<BankServer> bankServer_;
    static std::shared_ptr<CashBin> cashBin_;
    static CashCard cashCard_;
    static AccountInfo accountInfo;
};

class InitializingState : public AtmState
{
    AtmStateEnum getState() const override;
    void react(const Initialized &event) override;

    OperationResult initialize(
        std::shared_ptr<BankServer> bankServer,
        std::shared_ptr<CashBin> cashBin) override;
};

class IdleState : public AtmState
{
public:
    AtmStateEnum getState() const override;
    void react(const CardInserted &event) override;

    OperationResult insertCard(const CashCard &cashCard) override;
};

class ReadingCardState : public AtmState
{
public:
    AtmStateEnum getState() const override;
    void react(const ErrorOccured &event) override;
    void react(const CardVerified &event) override;
};

class ReadingPinState : public AtmState
{
public:
    AtmStateEnum getState() const override;
    void react(const Canceled &event) override;
    void react(const ErrorOccured &event) override;
    void react(const PinVerified &event) override;
};

class SelectingAccountState : public AtmState
{
public:
    AtmStateEnum getState() const override;
    void react(const Canceled &event) override;
    void react(const ErrorOccured &event) override;
    void react(const AccountSelected &event) override;
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
    void react(const CardEjected &event) override;
};

class OutOfCashState : public AtmState
{
public:
    AtmStateEnum getState() const override;
    void react(const CashRefilled &event) override;
};

class OutOfOrderState : public AtmState
{
public:
    AtmStateEnum getState() const override;
};

#endif  // ATM_STATE_H_
