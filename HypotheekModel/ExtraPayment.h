
#pragma once

#include "IHypotheekEvent.h"


namespace hypotheek {

class ExtraPayment
    : public IEvent
{
public:
    ExtraPayment(const Utils::Date& date, const Finance::Bedrag& payment);

    virtual hypotheekState nextState(const hypotheekState& state) const override;

private:
    Utils::Date m_date;
    Finance::Bedrag m_payment;
};

} // namespace hypotheek
