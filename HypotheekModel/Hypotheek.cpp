#include "Hypotheek.h"

#include <math.h>

#include "AflossingsvrijeHypotheek.h"
#include "AnnuitaireHypotheek.h"
#include "HypotheekDefinitions.h"

namespace hypotheek {

using Finance::Bedrag;

Hypotheek::Hypotheek()
    : mStartDate(Utils::Date::Today())
{
}

void Hypotheek::SetHypotheekBedrag(const Finance::Bedrag& bedrag)
{
    mBedrag = bedrag;
}

void Hypotheek::SetStartDate(const Utils::Date& date)
{
    mStartDate = date;
}

void Hypotheek::SetRentePercentage(const Percentage& jaarrente)
{
    mRentePercentage = jaarrente;
}

Percentage Hypotheek::effectiveMonthlyInterest() const
{
    return mRentePercentage.GetPercentage() / 12.0;
    //auto i = mRentePercentage.GetPercentage() * 0.01;
    //auto n = 12.0;
    //auto r = pow((1.0 + (i / n)), n) - 1;
    //auto r2 = (100.0 * r) / 12.0;
    //return r2;
    //auto r2 =  std::pow(1 + (mRentePercentage.GetPercentage() / 1200), 12);
    //return r2;
}

Finance::Bedrag Hypotheek::initialLoan() const
{
    return mBedrag;
}

hypotheek::Percentage Hypotheek::interestPercentage() const
{
    return mRentePercentage;
}

Utils::Date Hypotheek::StartDate() const
{
    return mStartDate;
}

std::unique_ptr<IHypotheek> CreateHypotheek(HYPOTHEEK_VORM vorm)
{
    switch (vorm) {
        case HYPOTHEEK_VORM::Aflossingsvrij:
            return std::make_unique<AflossingsvrijeHypotheek>();
        case HYPOTHEEK_VORM::Annuitair:
            return std::make_unique<AnnuitaireHypotheek>();
    }

    throw std::runtime_error("Hypotheek::CreateHypotheek: Invalid parameter " + std::to_string(int(vorm)));
}

} // namespace hypotheek