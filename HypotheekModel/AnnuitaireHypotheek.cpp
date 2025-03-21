#include "AnnuitaireHypotheek.h"

#include <math.h>       /* pow */

namespace Hypotheek {

Finance::Bedrag AnnuitaireHypotheek::GetMaandPremie() const
{
    double jaarrentefractie = mRentePercentage.GetPercentage() / 100;
    double maandrentefractie = jaarrentefractie / 12;
    int aantalPeriodes(30 * 12);
    auto annuiteit = (maandrentefractie / (1 - (pow(1 + maandrentefractie, -aantalPeriodes)))) * mBedrag.ToDouble();
    return Finance::Bedrag(annuiteit);
}

Finance::Bedrag AnnuitaireHypotheek::GetMaandPremie(const Utils::Date& month) const
{
    return GetMaandPremie();
}

Finance::Bedrag AnnuitaireHypotheek::GetJaarPremie() const
{
    return GetMaandPremie() * 12;
}

Finance::Bedrag AnnuitaireHypotheek::GetJaarPremie(int year) const
{
    return GetMaandPremie() * 12;
}

} // namespace Hypotheek