#ifndef ATM_STATE_H_
#define ATM_STATE_H_

#include "tinyfsm.hpp"
#include "operation-result.h"
#include "cash-card.h"
#include "pin-number.h"
#include "cash-bin.h"
#include "account.h"

#include <stdexcept>
#include <iostream>

// refs: https://www.geeksforgeeks.org/state-transition-diagram-for-an-atm-system/
struct Canceled : tinyfsm::Event { };
struct ErrorOccured : tinyfsm::Event
{
    OperationResult operationResult;
};
struct CardInserted : tinyfsm::Event { };
struct CardEjected : tinyfsm::Event { };
struct CardVerified : tinyfsm::Event { };
struct PinVerified : tinyfsm::Event { };
struct AccountSelected : tinyfsm::Event { };
struct TransactionChosen : tinyfsm::Event { };
struct TransactionContinued : tinyfsm::Event { };
struct TransactionFinished : tinyfsm::Event { };
struct OutOfCash : tinyfsm::Event { };
struct CashRefilled : tinyfsm::Event { };

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
    virtual void react(const OutOfCash &event) { };
    virtual void react(const CashRefilled &event) { };

    virtual void entry(void) { };
    void exit(void) { };

    virtual OperationResult insertCard(const CashCard &card) {
        return OperationResult(-1, "Invalid Operation");
    }
    virtual OperationResult ejectCard() {
        return OperationResult(-1, "Invalid Operation");
    }
    virtual OperationResult authenticate(const PinNumber &pin) {
        return OperationResult(-1, "Invalid Operation");
    }
    virtual OperationResult selectAccount(AccountType type) {
        return OperationResult(-1, "Invalid Operation");
    }

    virtual OperationResult seeBalance() {
        return OperationResult(-1, "Invalid Operation");
    }
    virtual OperationResult deposit(unsigned int amount) {
        return OperationResult(-1, "Invalid Operation");
    }
    virtual OperationResult withdraw(unsigned int amount) {
        return OperationResult(-1, "Invalid Operation");
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
    void react(const OutOfCash &event) override;
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
