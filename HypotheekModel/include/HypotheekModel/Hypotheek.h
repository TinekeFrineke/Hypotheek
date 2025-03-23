
#pragma once

#include <chrono>
#include <string>

#include <Utilities/Bedrag.h>
#include <Utilities/date.h>

#include "Percentage.h"
#include "IHypotheek.h"

namespace hypotheek
{

struct VasteBedragen;

class Hypotheek
    : public IHypotheek
    //, public Observer
{
public:
    Hypotheek();
    ~Hypotheek() override = default;

    void SetHypotheekBedrag(const Finance::Bedrag& bedrag) override;
    void SetStartDate(const Utils::Date& date) override;
    void SetRentePercentage(const Percentage& jaarrente) override;

    Percentage effectiveMonthlyInterest() const;

    Finance::Bedrag initialLoan() const override;
    hypotheek::Percentage interestPercentage() const override;
    Utils::Date StartDate() const override;

protected:
    Finance::Bedrag mBedrag;
    Percentage mRentePercentage;
    Utils::Date mStartDate;
};

} //  namespace hypotheek