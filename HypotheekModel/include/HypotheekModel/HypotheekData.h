
#pragma once

#include <Utilities/Bedrag.h>
#include <Utilities/Date.h>

#include "Percentage.h"

namespace hypotheek {

struct HypotheekData
{
    Utils::Date startDate;
    Finance::Bedrag payment;
    Finance::Bedrag interest;
    Finance::Bedrag repayment;
    Finance::Bedrag remainingDebt;
};

struct splitPayment
{
    Finance::Bedrag rente;
    Finance::Bedrag aflossing;
};

struct hypotheekState
{
    int periodesTeGaan;
    Percentage rente;
    Finance::Bedrag annuiteit;
    Finance::Bedrag restSchuld;
};



class NormalPayment
    : public IEvent
{
public:
 
    hypotheekState nextState(const hypotheekState& state) const override;

};

class ExtraPayment
    : public IEvent
{
public:
    ExtraPayment(const Finance::Bedrag& payment);
    hypotheekState nextState(const hypotheekState& state) const override;
};

} // namespace hypotheek