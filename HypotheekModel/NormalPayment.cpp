
#include "NormalPayment.h"

#include "HypotheekCalculation.h"

namespace hypotheek {

NormalPayment::NormalPayment(const Utils::Date& date)
    : m_date(date)
{
}

hypotheekState NormalPayment::nextState(const hypotheekState& state) const
{
    auto splitPayment = createSplitPayment(state);
    return { m_date, state.periodesTeGaan - 1, state.rente, state.annuiteit, state.restSchuld - splitPayment.aflossing };
}


} // namespace hypotheek
