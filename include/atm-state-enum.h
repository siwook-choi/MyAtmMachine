#ifndef ATM_STATE_ENUM_H_
#define ATM_STATE_ENUM_H_

// refs: https://www.geeksforgeeks.org/state-transition-diagram-for-an-atm-system/
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

#endif  // ATM_STATE_ENUM_H_
