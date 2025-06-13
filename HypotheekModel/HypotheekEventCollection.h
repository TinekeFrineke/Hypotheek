#pragma once

#include <map>

#include <utilities/Bedrag.h>
#include <utilities/Date.h>

#include "IHypotheekEventCollection.h"
#include "Percentage.h"


namespace hypotheek {

class EventCollection:
    public IEventCollection
{
public:
    EventCollection();
    virtual ~EventCollection();

    // Inherited via IEventCollection
    virtual void addEvent(const Utils::Date& date, std::unique_ptr<IEvent> event) override;
    virtual std::vector<HypotheekData> calculate() override;

private:
    std::map <Utils::Date, std::unique_ptr<IEvent>> m_events;
};

} // namespace hypotheek