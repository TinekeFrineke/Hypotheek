#include "AflossingsvrijeHypotheek.h"

#include <iostream>

namespace hypotheek {

Finance::Bedrag AflossingsvrijeHypotheek::GetMaandPremie() const
{
    auto bedrag = mRentePercentage.PercentageOf(mBedrag);
    bedrag = bedrag / 12;
    return mRentePercentage.PercentageOf(mBedrag) / 12;
}

Finance::Bedrag AflossingsvrijeHypotheek::GetMaandPremie(const Utils::Date& month) const
{
    auto bedrag = mRentePercentage.PercentageOf(mBedrag);
    bedrag = bedrag / 12;
    return mRentePercentage.PercentageOf(mBedrag) / 12;
}

Finance::Bedrag AflossingsvrijeHypotheek::GetJaarPremie() const
{
    std::cout << "GetJaarPremie() == " << GetMaandPremie() * 12;
    return GetMaandPremie() * 12;
}

Finance::Bedrag AflossingsvrijeHypotheek::GetJaarPremie(int year) const
{
    std::cout << "GetJaarPremie() == " << GetMaandPremie() * 12;
    return Finance::Bedrag();
}

Finance::Bedrag AflossingsvrijeHypotheek::maandRente(const Utils::Date& month) const
{
    return Finance::Bedrag();
}

Finance::Bedrag AflossingsvrijeHypotheek::maandAflossing(const Utils::Date& month) const
{
    return Finance::Bedrag();
}

Finance::Bedrag AflossingsvrijeHypotheek::maandRestSchuld(const Utils::Date& month) const
{
    return Finance::Bedrag();
}

Finance::Bedrag AflossingsvrijeHypotheek::jaarRente(const Utils::Date& month) const
{
    return Finance::Bedrag();
}

Finance::Bedrag AflossingsvrijeHypotheek::jaarAflossing(const Utils::Date& month) const
{
    return Finance::Bedrag();
}

Finance::Bedrag AflossingsvrijeHypotheek::jaarRestSchuld(const Utils::Date& month) const
{
    return Finance::Bedrag();
}

void AflossingsvrijeHypotheek::setExtraAflossing(const Utils::Date& date, const Finance::Bedrag& bedrag)
{
}

} // namespace hypotheek