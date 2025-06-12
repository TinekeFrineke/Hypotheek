#include "OverzichtCreator.h"

#include <fstream>

#include "AnnuitaireHypotheek.h"
#include "ExtraPayment.h"
#include "HypotheekEventCollection.h"
#include "NormalPayment.h"


namespace hypotheek {


void OverzichtCreator::visit(const AnnuitaireHypotheek& hypotheek)
{
    EventCollection collection(hypotheek.initialLoan(), hypotheek.interestPercentage(), 360, hypotheek.StartDate());

    Utils::Date startDate(hypotheek.StartDate());
    startDate.AddMonths(1);
    for (auto period = 0; period < 360; ++period) {
        collection.addEvent(startDate, std::make_unique<NormalPayment>(startDate));
        startDate.AddMonths(1);
    }

    const auto extraAflossingen{ hypotheek.getExtraAflossings() };
    for (auto aflossing : extraAflossingen)
        collection.addEvent(aflossing.first, std::make_unique<ExtraPayment>(aflossing.first, aflossing.second));

    auto data = collection.calculate();

    std::ofstream stream("C:\\Tineke\\hypotheek.txt");
    stream << "Startdatum - Aflossing - Rente - Resetschuld" << std::endl;
    for (const auto& entry : data) {
        stream << entry.startDate << " - " << entry.repayment << " - " << entry.interest << " - " << entry.remainingDebt << std::endl;
    }
}

void OverzichtCreator::visit(const AflossingsvrijeHypotheek& hypotheek)
{
}

} // namespace hypotheek