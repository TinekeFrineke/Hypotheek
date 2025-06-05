
#pragma once


#include "HypotheekData.h"


namespace hypotheek {

class IEvent
{
public:
    virtual ~IEvent() = default;

    virtual hypotheekState nextState(const hypotheekState& state) const = 0;
};

} // namespace hypotheek