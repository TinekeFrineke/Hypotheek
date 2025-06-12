
#include "HypotheekEventCollection.h"

#include <stdexcept>

#include "HypotheekCalculation.h"
#include "HypotheekData.h"
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
    if (m_events.find(date) != m_events.end())
        throw std::runtime_error("Duplicate date found!");
    m_events[date] = std::move(event);
}

std::vector<HypotheekData> EventCollection::calculate()
{
    HypotheekState state;
    state.datum = m_startDate;
    state.restSchuld = m_hypotheekBedrag;
    state.rente = m_jaarrente;
    state.periodesTeGaan = m_aantalPeriodes;
    state.annuiteit = calculateAnnuity(m_hypotheekBedrag, m_jaarrente, m_aantalPeriodes);

    std::vector<HypotheekData> hypotheekData;
    hypotheekData.push_back({ m_startDate, state.annuiteit, Finance::Bedrag(0.0), Finance::Bedrag(0.0), m_hypotheekBedrag });

    std::vector<HypotheekEntry> eventData;
    for (const auto& event : m_events) {
        auto result = event.second->nextState(state);
        hypotheekData.push_back({ result.state.datum, state.annuiteit, result.splitPayment.rente, result.splitPayment.aflossing, result.state.restSchuld });
        state = result.state;
    }
    
    return hypotheekData;
}

}