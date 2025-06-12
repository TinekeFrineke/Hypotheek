
#pragma once

#include <memory>
#include <vector>

namespace Utils {
class Date;
}

namespace hypotheek {

struct HypotheekData;
class IEvent;

class IEventCollection
{
public:
    virtual ~IEventCollection() = default;

    virtual void addEvent(const Utils::Date& date, std::unique_ptr<IEvent> event) = 0;
    virtual std::vector<HypotheekData> calculate() = 0;
};

} // namespace hypotheek