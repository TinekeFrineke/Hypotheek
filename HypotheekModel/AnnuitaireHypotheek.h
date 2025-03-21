#pragma once

#include "Hypotheek.h"

namespace Hypotheek {

class AnnuitaireHypotheek
    : public Hypotheek
{
    // Inherited via Hypotheek
    virtual Finance::Bedrag GetMaandPremie() const override;
    virtual Finance::Bedrag GetMaandPremie(const Utils::Date& month) const override;
    virtual Finance::Bedrag GetJaarPremie() const override;
    virtual Finance::Bedrag GetJaarPremie(int year) const override;
};

} // namespace Hypotheek
