#ifndef ATM_STATE_H_
#define ATM_STATE_H_

#include "atm-event.h"
#include "tinyfsm.hpp"
#include "operation-result.h"
#include "cash-card.h"
#include "pin-number.h"
#include "cash-bin.h"
#include "account.h"

#include <stdexcept>


// refs: https://www.geeksforgeeks.org/state-transition-diagram-for-an-atm-system/
enum class StateEnum
{
    IdleState,
    ReadingCardState,
    ReadingPinState,
    SelectingAccountState,
    ChoosingTransactionState,
    PerformingTransactionState,
    EjectingCardState,
    OutOfCashState
};

class AtmState : public tinyfsm::MooreMachine<AtmState>
{
public:
    virtual StateEnum getState() const = 0;

    void react(const tinyfsm::Event &event) {
        throw std::runtime_error("Unhandled event in AtmState");
    };

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

    virtual void entry(void) { };
    void exit(void) { };

    virtual OperationResult insertCard(const CashCard &card) {
        return OperationResult(OperationResult::ErrorCode::InvalidOperation, "Invalid Operation");
    }
    virtual OperationResult ejectCard() {
        return OperationResult(OperationResult::ErrorCode::InvalidOperation, "Invalid Operation");
    }
    virtual OperationResult authenticate(const PinNumber &pin) {
        return OperationResult(OperationResult::ErrorCode::InvalidOperation, "Invalid Operation");
    }
    virtual OperationResult selectAccount(AccountType type) {
        return OperationResult(OperationResult::ErrorCode::InvalidOperation, "Invalid Operation");
    }

    virtual OperationResult seeBalance() {
        return OperationResult(OperationResult::ErrorCode::InvalidOperation, "Invalid Operation");
    }
    virtual OperationResult deposit(unsigned int amount) {
        return OperationResult(OperationResult::ErrorCode::InvalidOperation, "Invalid Operation");
    }
    virtual OperationResult withdraw(unsigned int amount) {
        return OperationResult(OperationResult::ErrorCode::InvalidOperation, "Invalid Operation");
    }
};

class IdleState : public AtmState
{
public:
    StateEnum getState() const override;
    void react(const CardInserted &event) override;
};

class ReadingCardState : public AtmState
{
public:
    StateEnum getState() const override;
    void react(const ErrorOccured &event) override;
    void react(const CardVerified &event) override;
};

class ReadingPinState : public AtmState
{
public:
    StateEnum getState() const override;
    void react(const Canceled &event) override;
    void react(const ErrorOccured &event) override;
    void react(const PinVerified &event) override;
};

class SelectingAccountState : public AtmState
{
public:
    StateEnum getState() const override;
    void react(const Canceled &event) override;
    void react(const ErrorOccured &event) override;
    void react(const AccountSelected &event) override;
};

class ChoosingTransactionState : public AtmState
{
public:
    StateEnum getState() const override;
    void react(const Canceled &event) override;
    void react(const ErrorOccured &event) override;
    void react(const TransactionChosen &event) override;
};

class PerformingTransactionState : public AtmState
{
public:
    StateEnum getState() const override;
    void react(const Canceled &event) override;
    void react(const ErrorOccured &event) override;
    void react(const TransactionContinued &event) override;
    void react(const TransactionFinished &event) override;
};

class EjectingCardState : public AtmState
{
public:
    StateEnum getState() const override;
    void react(const CardEjected &event) override;
};

class OutOfCashState : public AtmState
{
public:
    StateEnum getState() const override;
    void react(const CashRefilled &event) override;
};

#endif  // ATM_STATE_H_
