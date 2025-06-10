
#include "HypotheekEventCollection.h"


#include "HypotheekCalculation.h"
#include "IHypotheekEvent.h"

namespace hypotheek {


EventCollection::EventCollection(const Finance::Bedrag& hypotheekBedrag, const Percentage& jaarrente, int aantalPeriodes, const Utils::Date& startDate)
    : m_startDate(startDate)
    , m_hypotheekBedrag(hypotheekBedrag)
    , m_jaarrente(jaarrente)
    , m_aantalPeriodes(aantalPeriodes)
{
}

void EventCollection::addEvent(const Utils::Date& date, std::unique_ptr<IEvent> event)
{
    m_events[date] = std::move(event);
}

std::vector<hypotheekEventData> EventCollection::calculate()
{
    hypotheekState state;
    state.datum = m_startDate;
    state.restSchuld = m_hypotheekBedrag;
    state.rente = m_jaarrente;
    state.periodesTeGaan = m_aantalPeriodes;
    state.annuiteit = calculateAnnuity(m_hypotheekBedrag, m_jaarrente, m_aantalPeriodes);

    std::vector<hypotheekEventData> eventData;
    eventData.push_back({ m_startDate, state });
    for (const auto& event : m_events) {
        state = event.second->nextState(state);
        eventData.push_back(hypotheekEventData{ event.first, state });
    }
    
    return eventData;
}

}