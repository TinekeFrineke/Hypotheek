
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
Finance::Bedrag calculateInterest(double fractionOfMonth, const Finance::Bedrag& restSchuld, const Percentage& jaarrente);
unsigned int daysInMonth(Utils::Date::MONTH month, int year);
double daysFraction(unsigned int dayFrom, unsigned int dayTo, Utils::Date::MONTH month, int year);


} // namespace hypotheek

