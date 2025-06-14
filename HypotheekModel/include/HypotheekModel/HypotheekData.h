
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

struct HypotheekState
{
    Utils::Date datum;
    int periodesTeGaan;
    Percentage rente;
    Finance::Bedrag annuiteit{0.0};
    Finance::Bedrag restSchuld{0.0};
};

struct HypotheekStepResult
{
    HypotheekState state;
    Finance::Bedrag rente;
    Finance::Bedrag aflossing;
};

} // namespace hypotheek