
#pragma once

#include "IHypotheekEvent.h"


namespace hypotheek {

class NormalPayment
    : public IEvent
{
public:
    NormalPayment(const Utils::Date& date);

    virtual HypotheekStepResult nextState(const HypotheekState& state) const override;

private:
    Utils::Date m_date;
};

} // namespace hypotheek