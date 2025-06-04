
#include "NormalPayment.h"

#include "HypotheekCalculation.h"

namespace hypotheek {

NormalPayment::NormalPayment()
{
}

hypotheekState ExtraPayment::nextState(const hypotheekState& state) const
{
    auto splitPament = createSplitPayment(state);
    return { state.periodesTeGaan - 1, state.rente, state.annuiteit, state.restSchuld - splitPament.aflossing };
}


} // namespace hypotheek