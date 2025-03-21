#include "AflossingsvrijeHypotheek.h"

namespace Hypotheek {

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

} // namespace Hypotheek