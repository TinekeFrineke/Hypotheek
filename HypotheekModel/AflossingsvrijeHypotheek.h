#pragma once

#include "Hypotheek.h"

namespace hypotheek {

class AflossingsvrijeHypotheek
    : public Hypotheek
{
    // Inherited via Hypotheek
    Finance::Bedrag GetMaandPremie() const override;
    Finance::Bedrag GetMaandPremie(const Utils::Date& month) const override;
    Finance::Bedrag GetJaarPremie() const override;
    Finance::Bedrag GetJaarPremie(int year) const override;

    Finance::Bedrag maandRente(const Utils::Date& month) const override;
    Finance::Bedrag maandAflossing(const Utils::Date& month) const override;
    Finance::Bedrag maandRestSchuld(const Utils::Date& month) const override;
    Finance::Bedrag jaarRente(const Utils::Date& month) const override;
    Finance::Bedrag jaarAflossing(const Utils::Date& month) const override;
    Finance::Bedrag jaarRestSchuld(const Utils::Date& month) const override;
    void accept(hypotheek::IVisitor& visitor) const override;
};

} // namespace hypotheek
