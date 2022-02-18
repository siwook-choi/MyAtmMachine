#ifndef ATM_STATE_ENUM_H_
#define ATM_STATE_ENUM_H_

#include "atm-machine-global.h"

BEGIN_ATM_MACHINE

enum class AtmStateEnum
{
    UndefinedState,
    InitializingState,
    IdleState,
    ReadingCardState,
    AuthenticatingState,
    SelectingAccountState,
    ChoosingTransactionState,
    PerformingTransactionState,
    EjectingCardState,
    OutOfCashState,
    OutOfOrderState
};

END_ATM_MACHINE

#endif  // ATM_STATE_ENUM_H_
