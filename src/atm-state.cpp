#include "atm-state.h"

FSM_INITIAL_STATE(AtmState, IdleState)

StateEnum IdleState::getState() const
{
    return StateEnum::IdleState;
}

void IdleState::react(const CardInserted &event)
{
    transit<ReadingCardState>();
}

StateEnum ReadingCardState::getState() const
{
    return StateEnum::ReadingCardState;
}

void ReadingCardState::react(const ErrorOccured &event)
{
    transit<EjectingCardState>();
}

void ReadingCardState::react(const CardVerified &event)
{
    transit<ReadingPinState>();
}

StateEnum ReadingPinState::getState() const
{
    return StateEnum::ReadingPinState;
}

void ReadingPinState::react(const Canceled &event)
{
    transit<EjectingCardState>();
}

void ReadingPinState::react(const ErrorOccured &event)
{
    transit<EjectingCardState>();
}

void ReadingPinState::react(const PinVerified &event)
{
    transit<SelectingAccountState>();
}

StateEnum SelectingAccountState::getState() const
{
    return StateEnum::SelectingAccountState;
}

void SelectingAccountState::react(const Canceled &event)
{
    transit<EjectingCardState>();
}

void SelectingAccountState::react(const ErrorOccured &event)
{
    transit<EjectingCardState>();
}

void SelectingAccountState::react(const AccountSelected &event)
{
    transit<ChoosingTransactionState>();
}

StateEnum ChoosingTransactionState::getState() const
{
    return StateEnum::ChoosingTransactionState;
}

void ChoosingTransactionState::react(const Canceled &event)
{
    transit<EjectingCardState>();
}

void ChoosingTransactionState::react(const ErrorOccured &event)
{
    transit<EjectingCardState>();
}

void ChoosingTransactionState::react(const TransactionChosen &event)
{
    transit<PerformingTransactionState>();
}

StateEnum PerformingTransactionState::getState() const
{
    return StateEnum::PerformingTransactionState;
}

void PerformingTransactionState::react(const Canceled &event)
{
    transit<EjectingCardState>();
}

void PerformingTransactionState::react(const ErrorOccured &event)
{
    if (event.result.getCode() == OperationResult::ErrorCode::OutOfCash) {
        transit<OutOfCashState>();
    } else {
        transit<EjectingCardState>();
    }
}

void PerformingTransactionState::react(const TransactionContinued &event)
{
    transit<ChoosingTransactionState>();
}

void PerformingTransactionState::react(const TransactionFinished &event)
{
    transit<EjectingCardState>();
}

StateEnum EjectingCardState::getState() const
{
    return StateEnum::EjectingCardState;
}

void EjectingCardState::react(const CardEjected &event)
{
    transit<IdleState>();
}

StateEnum OutOfCashState::getState() const
{
    return StateEnum::OutOfCashState;
}

void OutOfCashState::react(const CashRefilled &event)
{
    transit<IdleState>();
}