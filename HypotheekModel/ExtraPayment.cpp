
#include "ExtraPayment.h"

namespace hypotheek {

ExtraPayment::ExtraPayment(const Finance::Bedrag& payment)
    : m_payment(payment)
{
}

hypotheekState ExtraPayment::nextState(const hypotheekState& state) const
{
    if (m_payment.GetCenten() == 0 && m_payment.GetEuros() == 0)
        return state;

    double jaarrentefractie = state.rente.GetPercentage() / 100;
    double maandrentefractie = jaarrentefractie / 12;
    int aantalPeriodes(state.periodesTeGaan);
    double restschuld = (state.restSchuld - m_payment).ToDouble();
    auto annuiteit = (maandrentefractie / (1 - (pow(1 + maandrentefractie, -aantalPeriodes)))) * restschuld;
    return { state.periodesTeGaan, state.rente, Finance::Bedrag(annuiteit), restschuld };
}


} // namespace hypotheek