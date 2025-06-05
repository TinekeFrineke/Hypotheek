#include "OverzichtCreator.h"

#include <fstream>

#include "AnnuitaireHypotheek.h"
#include "ExtraPayment.h"
#include "HypotheekEventCollection.h"
#include "NormalPayment.h"


namespace hypotheek {


namespace {
Utils::Date addMonth(const Utils::Date& date) {
    if (date.Month() == Utils::Date::MONTH::December) {
        return Utils::Date { Utils::Date::DDay(date.Day()), Utils::Date::MONTH::January, Utils::Date::DYear(date.Year() + 1) };
    }
    else {
        return Utils::Date{ Utils::Date::DDay(date.Day()), static_cast<Utils::Date::MONTH>(static_cast<int>(date.Month()) + 1), Utils::Date::DYear(date.Year()) };
    }
}
}


void OverzichtCreator::visit(const AnnuitaireHypotheek& hypotheek)
{
    EventCollection collection(hypotheek.initialLoan(), hypotheek.interestPercentage(), 360, hypotheek.StartDate());

    Utils::Date startDate(hypotheek.StartDate());
    for (auto period = 0; period < 360; ++period) {
        collection.addEvent(startDate, std::make_unique<NormalPayment>());
        startDate = addMonth(startDate);
    }

    const auto extraAflossingen{ hypotheek.getExtraAflossings() };
    for (auto aflossing : extraAflossingen)
        collection.addEvent(aflossing.first, std::make_unique<ExtraPayment>(aflossing.second));

    auto data = collection.calculate();

    std::ofstream stream("C:\\Tineke\\hypotheek.txt");
    for (const auto& entry : data) {
        stream << entry.date << " - " << entry.state.annuiteit << " - " << entry.state.restSchuld << std::endl;
    }
}

void OverzichtCreator::visit(const AflossingsvrijeHypotheek& hypotheek)
{
}

} // namespace hypotheek