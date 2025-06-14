
#include "NormalPayment.h"

#include "HypotheekCalculation.h"

namespace hypotheek {

NormalPayment::NormalPayment(const Utils::Date& date)
    : m_date(date)
{
}

HypotheekStepResult NormalPayment::nextState(const HypotheekState& state) const
{
    double difference(state.datum.DaysDifference(m_date));
    auto daysinMonth = daysInMonth(state.datum.Month(), state.datum.Year());
    double fraction = difference / daysInMonth(state.datum.Month(), state.datum.Year());
    Finance::Bedrag interest = calculateInterest(fraction, state.restSchuld, state.rente);
    Finance::Bedrag aflossing = std::min(state.annuiteit - interest, state.restSchuld);
    return { { m_date, state.periodesTeGaan - 1, state.rente, state.annuiteit, state.restSchuld - aflossing }, interest, aflossing };
}


} // namespace hypotheek
