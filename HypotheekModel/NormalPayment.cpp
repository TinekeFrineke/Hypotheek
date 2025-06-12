
#include "NormalPayment.h"

#include "HypotheekCalculation.h"

namespace hypotheek {

NormalPayment::NormalPayment(const Utils::Date& date)
    : m_date(date)
{
}

HypotheekStepResult NormalPayment::nextState(const HypotheekState& state) const
{
    auto difference(state.datum.DaysDifference(m_date));
    double fraction = difference / daysInMonth(state.datum.Month(), state.datum.Year());
    auto splitPayment = createSplitPayment(fraction, state.annuiteit, state.rente, state.restSchuld);
//    auto splitPayment = createSplitPayment(state);
    return { { m_date, state.periodesTeGaan - 1, state.rente, state.annuiteit, state.restSchuld - splitPayment.aflossing }, splitPayment };
}


} // namespace hypotheek
