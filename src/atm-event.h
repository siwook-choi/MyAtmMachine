#ifndef ATM_EVENT_H_
#define ATM_EVENT_H_

#include "atm-machine-global.h"

#include <tinyfsm.hpp>
#include <operation-result.h>

BEGIN_ATM_MACHINE

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
struct CardRead : tinyfsm::Event { };
struct CardPulledOut : tinyfsm::Event { };
struct Authenticated : tinyfsm::Event { };
struct AccountSelected : tinyfsm::Event { };
struct TransactionChosen : tinyfsm::Event { };
struct TransactionFinished : tinyfsm::Event { };
struct CashRefilled : tinyfsm::Event { };

END_ATM_MACHINE

#endif  // ATM_EVENT_H_
