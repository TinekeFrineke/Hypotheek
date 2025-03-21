#pragma once

#include "Hypotheek.h"

namespace Hypotheek {

class AflossingsvrijeHypotheek
    : public Hypotheek
{
    // Inherited via Hypotheek
    Finance::Bedrag GetMaandPremie() const override;
    Finance::Bedrag GetMaandPremie(const Utils::Date& month) const override;
    Finance::Bedrag GetJaarPremie() const override;
    Finance::Bedrag GetJaarPremie(int year) const override;
};

} // namespace Hypotheek
