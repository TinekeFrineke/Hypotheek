
#pragma once

#include <vector>

class IHypotheek;

namespace hypotheek {

struct HypotheekData;

std::vector<HypotheekData> CreateMonthMetrics(const IHypotheek& hypotheek);


splitPayment createSplitPayment(const hypotheekState& state);


} // namespace hypotheek

