#pragma once

#include "Hypotheek.h"

namespace hypotheek {

class AnnuitaireHypotheek
    : public Hypotheek
{
public:
    AnnuitaireHypotheek();
    // Inherited via IHypotheek
    virtual Finance::Bedrag GetMaandPremie() const override;
    virtual Finance::Bedrag GetMaandPremie(const Utils::Date& month) const override;
    virtual Finance::Bedrag GetJaarPremie() const override;
    virtual Finance::Bedrag GetJaarPremie(int year) const override;
    virtual Finance::Bedrag maandRente(const Utils::Date& month) const override;
    virtual Finance::Bedrag maandAflossing(const Utils::Date& month) const override;
    virtual Finance::Bedrag maandRestSchuld(const Utils::Date& month) const override;
    virtual Finance::Bedrag jaarRente(const Utils::Date& month) const override;
    virtual Finance::Bedrag jaarAflossing(const Utils::Date& month) const override;
    virtual Finance::Bedrag jaarRestSchuld(const Utils::Date& month) const override;
    virtual void setExtraAflossing(const Utils::Date& date, const Finance::Bedrag& bedrag) override;
};

} // namespace hypotheek
