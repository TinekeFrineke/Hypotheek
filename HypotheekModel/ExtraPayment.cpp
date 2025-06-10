
#include "ExtraPayment.h"

#include <chrono>

#include "HypotheekCalculation.h"

namespace hypotheek {

ExtraPayment::ExtraPayment(const Utils::Date& date, const Finance::Bedrag& payment)
    : m_date(date)
    , m_payment(payment)
{
}

hypotheekState ExtraPayment::nextState(const hypotheekState& state) const
{
    if (m_payment.GetCenten() == 0 && m_payment.GetEuros() == 0)
        return state;

    double fraction = daysFraction(state.datum.Day(), m_date.Day(), m_date.Month(), m_date.Year());
    auto payment = createSplitPayment(fraction, state.annuiteit, state.rente, state.restSchuld);
    const auto aflossing = m_payment - payment.rente;
    const auto restschuld = state.restSchuld - aflossing;
    const auto annuiteit = calculateAnnuity(restschuld, state.rente, state.periodesTeGaan);

    return { m_date, state.periodesTeGaan, state.rente, annuiteit, restschuld };
}


} // namespace hypotheek