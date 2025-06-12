
#pragma once


#include "HypotheekData.h"


namespace hypotheek {

class IEvent
{
public:
    virtual ~IEvent() = default;

    virtual HypotheekStepResult nextState(const HypotheekState& state) const = 0;
};

} // namespace hypotheek