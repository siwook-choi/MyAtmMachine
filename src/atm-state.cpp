#include "atm-state.h"
#include "atm-machine.h"

FSM_INITIAL_STATE(AtmState, InitializingState)

std::function<void(AtmStateEnum)> AtmState::stateCallback_ = [](AtmStateEnum){};
std::shared_ptr<BankServer> AtmState::bankServer_ = nullptr;
std::shared_ptr<CashBin> AtmState::cashBin_ = nullptr;
std::shared_ptr<CardReader> AtmState::cardReader_ = nullptr;
CashCard AtmState::cashCard_ = CashCard();
PinNumber AtmState::pinNumber_ = PinNumber();
AccountSession AtmState::accountSession_ = AccountSession();

OperationResult AtmState::release()
{
    AtmState::set_initial_state();
    stateCallback_ = [](AtmStateEnum){};
    bankServer_= nullptr;
    cashBin_ = nullptr;
    cardReader_ = nullptr;
    cashCard_ = CashCard();
    pinNumber_ = PinNumber();
    accountSession_ = AccountSession();

    return OperationResult(ErrorCode::Ok, "");
}

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
        std::shared_ptr<CashBin> cashBin,
        std::shared_ptr<CardReader> cardReader)
{
    bankServer_ = bankServer;
    cashBin_ = cashBin;
    cardReader_ = cardReader;
    dispatch(Initialized());
    return OperationResult(ErrorCode::Ok, "");
}

AtmStateEnum IdleState::getState() const
{
    return AtmStateEnum::IdleState;
}

void IdleState::react(const ErrorOccured &event)
{
    if (event.result.isFatal())
        transit<OutOfOrderState>();
}

void IdleState::react(const CardInserted &event)
{
    if (cardReader_->hasCard())
        transit<ReadingCardState>();
}

AtmStateEnum ReadingCardState::getState() const
{
    return AtmStateEnum::ReadingCardState;
}

void ReadingCardState::react(const ErrorOccured &event)
{
    if (event.result.isFatal()) {
        transit<OutOfOrderState>();
    } else {
        transit<EjectingCardState>();
    }
}

void ReadingCardState::react(const CardRead &event)
{
    transit<AuthenticatingState>();
}

void ReadingCardState::entry()
{
    CashCard cashCard;
    const auto result = cardReader_->readCard(cashCard);

    if (result.isSucceed()) {
        dispatch(CardRead());
    } else {
        dispatch(ErrorOccured(result));
    }
}

AtmStateEnum AuthenticatingState::getState() const
{
    return AtmStateEnum::AuthenticatingState;
}

void AuthenticatingState::react(const Canceled &event)
{
    transit<EjectingCardState>();
}

void AuthenticatingState::react(const ErrorOccured &event)
{
    if (event.result.isFatal()) {
        transit<OutOfOrderState>();
    } else {
        transit<EjectingCardState>();
    }
}

void AuthenticatingState::react(const Authenticated &event)
{
    transit<SelectingAccountState>();
}

OperationResult AuthenticatingState::enterPin(const PinNumber &pinNumber)
{
    const auto result = bankServer_->authenticate(cashCard_, pinNumber);
    
    if (result.isSucceed()) {
        pinNumber_ = pinNumber;
        dispatch(Authenticated());
    } else {
        dispatch(ErrorOccured(result));
    }
    
    return result;
}

OperationResult AuthenticatingState::cancel()
{
    dispatch(Canceled());
    return OperationResult(ErrorCode::Ok, "");
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
        transit<OutOfOrderState>();
    } else {
        transit<EjectingCardState>();
    }
}

void SelectingAccountState::react(const AccountSelected &event)
{
    transit<ChoosingTransactionState>();
}

OperationResult SelectingAccountState::selectAccount(AccountType accountType)
{
    AccountSession accountSession;
    const auto result = bankServer_->selectAccount(cashCard_, pinNumber_, accountType, accountSession);

    if (result.isSucceed()) {
        accountSession_ = accountSession;
        dispatch(AccountSelected());
    } else {
        dispatch(ErrorOccured(result));
    }

    return result;
}

OperationResult SelectingAccountState::cancel()
{
    dispatch(Canceled());
    return OperationResult(ErrorCode::Ok, "");
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
        transit<OutOfOrderState>();
    } else {
        transit<EjectingCardState>();
    }
}

void ChoosingTransactionState::react(const TransactionChosen &event)
{
    transit<PerformingTransactionState>();
}

OperationResult ChoosingTransactionState::seeBalance(AccountInfo &accountInfo)
{
    dispatch(TransactionChosen());
    const auto result = bankServer_->seeBalance(accountSession_, accountInfo);

    if (result.isSucceed()) {
        dispatch(TransactionFinished());
    } else {
        dispatch(ErrorOccured(result));
    }

    return result;
}

OperationResult ChoosingTransactionState::deposit(unsigned int amount)
{
    dispatch(TransactionChosen());
    const auto result = bankServer_->deposit(accountSession_, amount);

    if (result.isSucceed()) {
        dispatch(TransactionFinished());
    } else {
        dispatch(ErrorOccured(result));
    }

    return result;
}

OperationResult ChoosingTransactionState::withdraw(unsigned int amount)
{
    dispatch(TransactionChosen());
    
    {
        const auto result = checkCashBinAmount(amount);
        if (!result.isSucceed()) {
            dispatch(ErrorOccured(result));
            return result;
        }
    }

    {
        const auto result = bankServer_->withdraw(accountSession_, amount);
        if (!result.isSucceed()) {
            dispatch(ErrorOccured(result));
            return result;
        }
    }

    {
        const auto result = cashBin_->dispenseCash(amount);
        if (!result.isSucceed()) {
            dispatch(ErrorOccured(result));
            return result;
        }
    }
    
    dispatch(TransactionFinished());
    return OperationResult(ErrorCode::Ok, "");
}

OperationResult ChoosingTransactionState::checkCashBinAmount(unsigned int amount)
{
    OperationResult result(ErrorCode::Ok, "");
    if (cashBin_->getAmountCash() < amount) {
        result = OperationResult(ErrorCode::OutOfCash, "Not enough cash");
    }

    return result;
}

OperationResult ChoosingTransactionState::cancel()
{
    dispatch(Canceled());
    return OperationResult(ErrorCode::Ok, "");
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
        transit<OutOfOrderState>();
    } else if (event.result.getCode() == ErrorCode::OutOfCash) {
        transit<OutOfCashState>();
    } else {
        transit<EjectingCardState>();
    }
}

void PerformingTransactionState::react(const TransactionFinished &event)
{
    transit<ChoosingTransactionState>();
}

AtmStateEnum EjectingCardState::getState() const
{
    return AtmStateEnum::EjectingCardState;
}

void EjectingCardState::react(const CardPulledOut &event)
{
    transit<IdleState>();
}

void EjectingCardState::entry()
{
    AtmState::entry();

    cashCard_ = CashCard();
    pinNumber_ = PinNumber();
    accountSession_ = AccountSession();

    if (cardReader_->hasCard())
        cardReader_->ejectCard();
}

AtmStateEnum OutOfCashState::getState() const
{
    return AtmStateEnum::OutOfCashState;
}

void OutOfCashState::react(const CashRefilled &event)
{
    transit<IdleState>();
}

void OutOfCashState::entry()
{
    AtmState::entry();

    cashCard_ = CashCard();
    pinNumber_ = PinNumber();
    accountSession_ = AccountSession();

    if (cardReader_->hasCard())
        cardReader_->ejectCard();
}

AtmStateEnum OutOfOrderState::getState() const
{
    return AtmStateEnum::OutOfOrderState;
}

void OutOfOrderState::entry()
{
    AtmState::entry();

    cashCard_ = CashCard();
    pinNumber_ = PinNumber();
    accountSession_ = AccountSession();

    if (cardReader_->hasCard())
        cardReader_->ejectCard();
}
