
#include "ExtraPayment.h"

#include <chrono>

#include "HypotheekCalculation.h"

namespace hypotheek {

ExtraPayment::ExtraPayment(const Utils::Date& date, const Finance::Bedrag& payment)
    : m_date(date)
    , m_payment(payment)
{
}

HypotheekStepResult ExtraPayment::nextState(const HypotheekState& state) const
{
    double fraction = daysFraction(state.datum.Day(), m_date.Day(), m_date.Month(), m_date.Year());
    // Calculate the interest that was built up this month up to the payment
    auto rente = calculateInterest(fraction, state.restSchuld, state.rente);
    const auto aflossing = m_payment - rente;
    if (aflossing.IsNegative())
        throw std::invalid_argument("Payment " + m_payment.ToString() + " will lead to negative repayment");

    const auto restschuld = state.restSchuld - aflossing;
    const auto annuiteit = calculateAnnuity(restschuld, state.rente, state.periodesTeGaan);

    return { { m_date, state.periodesTeGaan, state.rente, annuiteit, restschuld }, { rente, aflossing } };
}


} // namespace hypotheek