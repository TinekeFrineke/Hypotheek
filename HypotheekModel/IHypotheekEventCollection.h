
#pragma once

#include <memory>
#include <vector>

#include <Utilities/date.h>

#include "HypotheekData.h"


namespace hypotheek {

class IEvent;

class IEventCollection
{
public:
    virtual ~IEventCollection() = default;

    virtual void addEvent(const Utils::Date& date, std::unique_ptr<IEvent> event) = 0;
    virtual std::vector<hypotheekEventData> calculate() = 0;
};

} // namespace hypotheek