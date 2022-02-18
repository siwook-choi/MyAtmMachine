#include "atm-machine.h"
#include "atm-state.h"

AtmStateEnum AtmMachine::getState()
{
    return AtmState::current_state_ptr->getState();
}

OperationResult AtmMachine::initialize(std::shared_ptr<BankServer> bankServer, std::shared_ptr<CashBin> cashBin)
{
    return AtmState::current_state_ptr->initialize(bankServer, cashBin);
}

OperationResult AtmMachine::insertCard(const CashCard &cashCard)
{
    return AtmState::current_state_ptr->insertCard(cashCard);
}

OperationResult AtmMachine::ejectCard()
{
    return AtmState::current_state_ptr->ejectCard();
}

OperationResult AtmMachine::enterPin(const PinNumber &pinNumber)
{
    return AtmState::current_state_ptr->enterPin(pinNumber);
}

OperationResult AtmMachine::selectAccount(AccountType accountType)
{
    return AtmState::current_state_ptr->selectAccount(accountType);
}

OperationResult AtmMachine::seeBalance()
{
    return AtmState::current_state_ptr->seeBalance();
}

OperationResult AtmMachine::deposit(unsigned int amount)
{
    return AtmState::current_state_ptr->deposit(amount);
}

OperationResult AtmMachine::withdraw(unsigned int amount)
{
    return AtmState::current_state_ptr->withdraw(amount);
}

void setStateCallback(std::function<void(AtmStateEnum)> stateCallback)
{
    AtmState::setStateCallback(stateCallback);
}
