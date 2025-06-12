
#pragma once

#include <vector>

#include <utilities/Date.h>

namespace Finance {
class Bedrag;
}

class IHypotheek;

namespace hypotheek {

class Percentage;

struct HypotheekData;
struct HypotheekState;
struct SplitPayment;

Finance::Bedrag calculateAnnuity(const Finance::Bedrag& restSchuld, const Percentage& jaarrente, int aantalPeriodes);
// Splits the annuity in the interest and the repayment
SplitPayment createSplitPayment(const HypotheekState& state);
// Splits the annuity in the interest and the repayment
SplitPayment createSplitPayment(const Finance::Bedrag annuiteit, const Percentage& jaarrente, const Finance::Bedrag& restSchuld);
// Calculates all values for fractionOfMonth * monthly values
SplitPayment createSplitPayment(double fractionOfMonth, const Finance::Bedrag annuiteit, const Percentage& jaarrente, const Finance::Bedrag& restSchuld);
unsigned int daysInMonth(Utils::Date::MONTH month, int year);
double daysFraction(unsigned int dayFrom, unsigned int dayTo, Utils::Date::MONTH month, int year);


} // namespace hypotheek

