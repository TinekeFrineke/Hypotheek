
#pragma once

#include "IHypotheekEvent.h"

#include <utilities/Bedrag.h>
#include <utilities/Date.h>

#include "Percentage.h"


namespace hypotheek {

class FirstEmptyPayment
    : public IEvent
{
public:
    FirstEmptyPayment(const Utils::Date& date, const Finance::Bedrag restSchuld, const Percentage& rente, int periodesTeGaan);

    virtual HypotheekStepResult nextState(const HypotheekState& state) const override;

private:
    Utils::Date m_date;
    Finance::Bedrag m_restSchuld;
    Percentage m_rente;
    int m_periodesTeGaan;
};

} // namespace hypotheek