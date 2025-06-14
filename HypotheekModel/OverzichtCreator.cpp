#include "OverzichtCreator.h"

#include <fstream>

#include "AnnuitaireHypotheek.h"
#include "ExtraPayment.h"
#include "FirstEmptyPayment.h"
#include "HypotheekEventCollection.h"
#include "NormalPayment.h"


namespace hypotheek {


void OverzichtCreator::visit(const AnnuitaireHypotheek& hypotheek)
{
    EventCollection collection;

    Utils::Date startDate(hypotheek.StartDate());

    collection.addEvent(startDate, std::make_unique<FirstEmptyPayment>(startDate, hypotheek.initialLoan(), hypotheek.interestPercentage(), hypotheek.numberOfMonths()));

    startDate.AddMonths(1);
    for (auto period = 1; period <= hypotheek.numberOfMonths(); ++period) {
        collection.addEvent(startDate, std::make_unique<NormalPayment>(startDate));
        startDate.AddMonths(1);
    }

    const auto extraAflossingen{ hypotheek.getExtraAflossings() };
    for (auto aflossing : extraAflossingen)
        collection.addEvent(aflossing.first, std::make_unique<ExtraPayment>(aflossing.first, aflossing.second));

    m_result = collection.calculate();
}

void OverzichtCreator::visit(const AflossingsvrijeHypotheek& hypotheek)
{
}

} // namespace hypotheek