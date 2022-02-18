#include "atm-machine.h"
#include "atm-state.h"

BEGIN_ATM_MACHINE

AtmStateEnum AtmMachine::getState()
{
    return AtmState::current_state_ptr->getState();
}

OperationResult AtmMachine::initialize(
    std::shared_ptr<BankServer> bankServer,
    std::shared_ptr<CashBin> cashBin,
    std::shared_ptr<CardReader> cardReader)
{
    AtmState::start();
    return AtmState::current_state_ptr->initialize(bankServer, cashBin, cardReader);
}

OperationResult AtmMachine::release()
{
    return AtmState::current_state_ptr->release();
}

OperationResult AtmMachine::enterPin(const PinNumber &pinNumber)
{
    return AtmState::current_state_ptr->enterPin(pinNumber);
}

OperationResult AtmMachine::selectAccount(AccountType accountType)
{
    return AtmState::current_state_ptr->selectAccount(accountType);
}

OperationResult AtmMachine::seeBalance(AccountInfo &accountInfo)
{
    return AtmState::current_state_ptr->seeBalance(accountInfo);
}

OperationResult AtmMachine::deposit()
{
    return AtmState::current_state_ptr->deposit();
}

OperationResult AtmMachine::withdraw(unsigned int amount)
{
    return AtmState::current_state_ptr->withdraw(amount);
}

OperationResult AtmMachine::cancel()
{
    return AtmState::current_state_ptr->cancel();
}

void setStateCallback(std::function<void(AtmStateEnum)> stateCallback)
{
    AtmState::setStateCallback(stateCallback);
}

END_ATM_MACHINE
