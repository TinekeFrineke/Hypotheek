
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
struct hypotheekState;
struct splitPayment;

std::vector<HypotheekData> CreateMonthMetrics(const IHypotheek& hypotheek);

Finance::Bedrag calculateAnnuity(const Finance::Bedrag& restSchuld, const Percentage& jaarrente, int aantalPeriodes);
// Splits the annuity in the interest and the repayment
splitPayment createSplitPayment(const hypotheekState& state);
// Splits the annuity in the interest and the repayment
splitPayment createSplitPayment(const Finance::Bedrag annuiteit, const Percentage& jaarrente, const Finance::Bedrag& restSchuld);
// Calculates all values for fractionOfMonth * monthly values
splitPayment createSplitPayment(double fractionOfMonth, const Finance::Bedrag annuiteit, const Percentage& jaarrente, const Finance::Bedrag& restSchuld);
unsigned int daysInMonth(Utils::Date::MONTH month, int year);
double daysFraction(unsigned int dayFrom, unsigned int dayTo, Utils::Date::MONTH month, int year);


} // namespace hypotheek

