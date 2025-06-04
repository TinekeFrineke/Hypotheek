
#pragma once

#include "IHypotheekEvent.h"


namespace hypotheek {

class NormalPayment
    : public IEvent
{
public:
    NormalPayment();

    virtual hypotheekState nextState(const hypotheekState& state) const override;
};

} // namespace hypotheek