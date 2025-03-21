#include "Hypotheek.h"

#include <math.h>

#include "AflossingsvrijeHypotheek.h"
#include "AnnuitaireHypotheek.h"
#include "HypotheekDefinitions.h"

namespace Hypotheek {

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

Percentage Hypotheek::EffectieveMaandRente() const
{
    return std::pow(1 + (mRentePercentage.GetPercentage() / 12), 12);
}

std::shared_ptr<IHypotheek> CreateHypotheek(HYPOTHEEK_VORM vorm)
{
    switch (vorm) {
    case HYPOTHEEK_VORM::Aflossingsvrij:
        return std::make_shared<AflossingsvrijeHypotheek>();
    case HYPOTHEEK_VORM::Annuitair:
        return std::make_shared<AnnuitaireHypotheek>();
    }

    throw std::runtime_error("Hypotheek::CreateHypotheek: Invalid parameter " + std::to_string(int(vorm)));
}

} // namespace Hypotheek