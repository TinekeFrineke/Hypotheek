
#include "HypotheekEventCollection.h"

#include <stdexcept>

#include "HypotheekCalculation.h"
#include "HypotheekData.h"
#include "IHypotheekEvent.h"

namespace hypotheek {


EventCollection::EventCollection()
{
}

EventCollection::~EventCollection() = default;

void EventCollection::addEvent(const Utils::Date& date, std::unique_ptr<IEvent> event)
{
    if (m_events.find(date) != m_events.end())
        throw std::runtime_error("Duplicate date found!");
    m_events[date] = std::move(event);
}

std::vector<HypotheekData> EventCollection::calculate()
{
    HypotheekState state{};

    std::vector<HypotheekData> hypotheekData;
    std::vector<HypotheekEntry> eventData;
    for (const auto& event : m_events) {
        auto result = event.second->nextState(state);
        hypotheekData.push_back({ result.state.datum, state.annuiteit, result.splitPayment.rente, result.splitPayment.aflossing, result.state.restSchuld });
        state = result.state;
    }
    
    return hypotheekData;
}

}