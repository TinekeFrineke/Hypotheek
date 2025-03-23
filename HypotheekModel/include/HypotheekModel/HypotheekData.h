
#pragma once

#include <Utilities/Bedrag.h>
#include <Utilities/Date.h>


namespace hypotheek {

struct HypotheekData
{
    Utils::Date startDate;
    Finance::Bedrag payment;
    Finance::Bedrag interest;
    Finance::Bedrag repayment;
    Finance::Bedrag remainingDebt;
};

} // namespace hypotheek