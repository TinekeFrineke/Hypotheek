
#pragma once

#include <vector>

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
splitPayment createSplitPayment(const hypotheekState& state);


} // namespace hypotheek

