
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
    Utils::Date datum;
    int periodesTeGaan;
    Percentage rente;
    Finance::Bedrag annuiteit;
    Finance::Bedrag restSchuld;
};

struct hypotheekEventData {
    Utils::Date date;
    hypotheekState state;
};


} // namespace hypotheek