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
    EventCollection(const Finance::Bedrag& hypotheekBedrag, const Percentage& jaarrente, int aantalPeriodes, const Utils::Date& startDate);

    // Inherited via IEventCollection
    virtual void addEvent(const Utils::Date& date, std::unique_ptr<IEvent> event) override;
    virtual std::vector<HypotheekData> calculate() override;

private:
    Utils::Date m_startDate;
    Finance::Bedrag m_hypotheekBedrag;
    Percentage m_jaarrente;
    int m_aantalPeriodes;
    std::map <Utils::Date, std::unique_ptr<IEvent>> m_events;
};

} // namespace hypotheek