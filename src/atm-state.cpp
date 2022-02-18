#include "atm-state.h"
#include "atm-machine.h"

FSM_INITIAL_STATE(AtmState, InitializingState)

std::function<void(AtmStateEnum)> AtmState::stateCallback_ = [](AtmStateEnum){};
std::shared_ptr<BankServer> AtmState::bankServer_ = nullptr;
std::shared_ptr<CashBin> AtmState::cashBin_ = nullptr;
CashCard AtmState::cashCard_ = CashCard();
AccountInfo AtmState::accountInfo = AccountInfo();

AtmStateEnum InitializingState::getState() const
{
    return AtmStateEnum::InitializingState;
}

void InitializingState::react(const Initialized &event)
{
    transit<IdleState>();
}

OperationResult InitializingState::initialize(
        std::shared_ptr<BankServer> bankServer,
        std::shared_ptr<CashBin> cashBin)
{
    bankServer_ = bankServer;
    cashBin_ = cashBin;
    AtmState::dispatch(Initialized());
    return OperationResult(ErrorCode::Ok, "");
}

AtmStateEnum IdleState::getState() const
{
    return AtmStateEnum::IdleState;
}

void IdleState::react(const CardInserted &event)
{
    transit<ReadingCardState>();
}

OperationResult IdleState::insertCard(const CashCard &cashCard)
{
    cashCard_ = cashCard;
    return OperationResult(ErrorCode::Ok, "");
}

AtmStateEnum ReadingCardState::getState() const
{
    return AtmStateEnum::ReadingCardState;
}

void ReadingCardState::react(const ErrorOccured &event)
{
    if (event.result.isFatal()) {
        ejectCard();
        transit<OutOfOrderState>();
    } else {
        transit<EjectingCardState>();
    }
}

void ReadingCardState::react(const CardVerified &event)
{
    transit<ReadingPinState>();
}

AtmStateEnum ReadingPinState::getState() const
{
    return AtmStateEnum::ReadingPinState;
}

void ReadingPinState::react(const Canceled &event)
{
    transit<EjectingCardState>();
}

void ReadingPinState::react(const ErrorOccured &event)
{
    if (event.result.isFatal()) {
        ejectCard();
        transit<OutOfOrderState>();
    } else {
        transit<EjectingCardState>();
    }
}

void ReadingPinState::react(const PinVerified &event)
{
    transit<SelectingAccountState>();
}

AtmStateEnum SelectingAccountState::getState() const
{
    return AtmStateEnum::SelectingAccountState;
}

void SelectingAccountState::react(const Canceled &event)
{
    transit<EjectingCardState>();
}

void SelectingAccountState::react(const ErrorOccured &event)
{
    if (event.result.isFatal()) {
        ejectCard();
        transit<OutOfOrderState>();
    } else {
        transit<EjectingCardState>();
    }
}

void SelectingAccountState::react(const AccountSelected &event)
{
    transit<ChoosingTransactionState>();
}

AtmStateEnum ChoosingTransactionState::getState() const
{
    return AtmStateEnum::ChoosingTransactionState;
}

void ChoosingTransactionState::react(const Canceled &event)
{
    transit<EjectingCardState>();
}

void ChoosingTransactionState::react(const ErrorOccured &event)
{
    if (event.result.isFatal()) {
        ejectCard();
        transit<OutOfOrderState>();
    } else {
        transit<EjectingCardState>();
    }
}

void ChoosingTransactionState::react(const TransactionChosen &event)
{
    transit<PerformingTransactionState>();
}

AtmStateEnum PerformingTransactionState::getState() const
{
    return AtmStateEnum::PerformingTransactionState;
}

void PerformingTransactionState::react(const Canceled &event)
{
    transit<EjectingCardState>();
}

void PerformingTransactionState::react(const ErrorOccured &event)
{
    if (event.result.isFatal()) {
        ejectCard();
        transit<OutOfOrderState>();
    } else if (event.result.getCode() == ErrorCode::OutOfCash) {
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

AtmStateEnum EjectingCardState::getState() const
{
    return AtmStateEnum::EjectingCardState;
}

void EjectingCardState::react(const CardEjected &event)
{
    transit<IdleState>();
}

AtmStateEnum OutOfCashState::getState() const
{
    return AtmStateEnum::OutOfCashState;
}

void OutOfCashState::react(const CashRefilled &event)
{
    transit<IdleState>();
}

AtmStateEnum OutOfOrderState::getState() const
{
    return AtmStateEnum::OutOfOrderState;
}
