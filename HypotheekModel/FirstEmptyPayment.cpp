
#include "FirstEmptyPayment.h"

#include "HypotheekCalculation.h"

namespace hypotheek {

FirstEmptyPayment::FirstEmptyPayment(const Utils::Date& date, const Finance::Bedrag restSchuld, const Percentage& rente, int periodesTeGaan)
    : m_date(date)
    , m_restSchuld(restSchuld)
    , m_rente(rente)
    , m_periodesTeGaan(periodesTeGaan)
{
}

HypotheekStepResult FirstEmptyPayment::nextState(const HypotheekState& state) const
{
    auto annuiteit = calculateAnnuity(m_restSchuld, m_rente, m_periodesTeGaan);

    return { { m_date, m_periodesTeGaan, m_rente, annuiteit, m_restSchuld }, Finance::Bedrag(0.0), Finance::Bedrag(0.0) };
}


} // namespace hypotheek
