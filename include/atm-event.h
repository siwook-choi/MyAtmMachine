#ifndef ATM_EVENT_H_
#define ATM_EVENT_H_

#include <tinyfsm.hpp>
#include <operation-result.h>

struct Initialized : tinyfsm::Event { };
struct Canceled : tinyfsm::Event { };
struct ErrorOccured : tinyfsm::Event
{
    ErrorOccured(const OperationResult result = OperationResult()) {
        this->result = result;
    }
    OperationResult result;
};
struct CardInserted : tinyfsm::Event { };
struct CardPulledOut : tinyfsm::Event { };
struct CardVerified : tinyfsm::Event { };
struct PinVerified : tinyfsm::Event { };
struct AccountSelected : tinyfsm::Event { };
struct TransactionChosen : tinyfsm::Event { };
struct TransactionContinued : tinyfsm::Event { };
struct TransactionFinished : tinyfsm::Event { };
struct CashRefilled : tinyfsm::Event { };

#endif  // ATM_EVENT_H_
