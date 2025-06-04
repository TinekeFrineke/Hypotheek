
#pragma once

#include "IHypotheekEvent.h"


namespace hypotheek {

class ExtraPayment
    : public IEvent
{
public:
    ExtraPayment(const Finance::Bedrag& payment);

    virtual hypotheekState nextState(const hypotheekState& state) const override;

private:
    Finance::Bedrag m_payment;
};

} // namespace hypotheek
