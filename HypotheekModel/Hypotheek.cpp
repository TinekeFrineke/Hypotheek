#include "Hypotheek.h"

#include <math.h>
#include <stdexcept>

#include "AflossingsvrijeHypotheek.h"
#include "AnnuitaireHypotheek.h"
#include "HypotheekDefinitions.h"

namespace hypotheek {

using Finance::Bedrag;

Hypotheek::Hypotheek()
    : mStartDate(Utils::Today())
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

void Hypotheek::setExtraAflossing(const Utils::Date& date, const Finance::Bedrag& bedrag)
{
    if (m_extraAflossings.find(date) == m_extraAflossings.end())
        m_extraAflossings[date] = bedrag;
    else
        m_extraAflossings[date] += bedrag;
}

std::map<Utils::Date, Finance::Bedrag> Hypotheek::getExtraAflossings() const
{
    return m_extraAflossings;
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