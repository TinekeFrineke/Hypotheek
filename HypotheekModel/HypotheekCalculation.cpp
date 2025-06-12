
#include "HypotheekCalculation.h"

#include <chrono>

#include <Utilities/Bedrag.h>
#include <Utilities/Date.h>

#include "IHypotheek.h"
#include "HypotheekData.h"
#include "Percentage.h"

namespace hypotheek {

namespace {
class MonthlyDate
{
public:
    MonthlyDate(const Utils::Date& date)
        : month(static_cast<int>(date.Month()))
        , year(date.Year())
    {
    }

    MonthlyDate& operator++()
    {
        if (month == static_cast<int>(Utils::Date::MONTH::December)) {
            month = static_cast<int>(Utils::Date::MONTH::January);
            ++year;
        }
        else
            ++month;
        return *this;
    }

    MonthlyDate operator++(int)
    {
        MonthlyDate date(*this);
        operator++();
        return date;
    }

    Utils::Date date() const
    {
        return Utils::Date(Utils::Date::DDay(1), static_cast<Utils::Date::MONTH>(month), Utils::Date::DYear(year));
    }

private:
    int month;
    int year;
};

double roundup(double input) {
    auto result1 = (input + 0.005) * 100;
    auto result2 = (int)result1;
    auto result3 = double(result2) / 100.0;
    return result3;
}

}

Finance::Bedrag calculateAnnuity(const Finance::Bedrag& restSchuld, const Percentage& jaarrente, int aantalPeriodes)
{
    double jaarrentefractie = jaarrente.GetPercentage() / 100;
    double maandrentefractie = jaarrentefractie / 12;
    auto annuiteit = (maandrentefractie / (1 - (pow(1 + maandrentefractie, -aantalPeriodes)))) * restSchuld.ToDouble();
    return Finance::Bedrag(annuiteit);
}

SplitPayment createSplitPayment(const HypotheekState& state)
{
    return createSplitPayment(1, state.annuiteit, state.rente, state.restSchuld);
}

SplitPayment createSplitPayment(const Finance::Bedrag monthAnnuity, const Percentage& interest, const Finance::Bedrag& debt)
{
    return createSplitPayment(1, monthAnnuity, interest, debt);
}

SplitPayment createSplitPayment(double fractionOfMonth, const Finance::Bedrag monthAnnuity, const Percentage& interest, const Finance::Bedrag& debt)
{
    Finance::Bedrag payment{ monthAnnuity.ToDouble() * fractionOfMonth };
    auto renteBedrag = Finance::Bedrag(debt.ToDouble() * fractionOfMonth * (interest.GetPercentage() / 12) / 100);
    auto aflossing = payment - renteBedrag;
    return { renteBedrag, aflossing };
}

unsigned int daysInMonth(Utils::Date::MONTH month, int year)
{
    auto ym = std::chrono::year_month{ std::chrono::year{year}, std::chrono::month{static_cast<unsigned int>(month)} };
    auto ymdl = std::chrono::year_month_day_last{ ym / std::chrono::last };
    return static_cast<unsigned>(ymdl.day());
}

double daysFraction(unsigned int dayFrom, unsigned int dayTo, Utils::Date::MONTH month, int year)
{
    auto nrOfDaysInMonth = daysInMonth(month, year);
    unsigned int diff = abs((int(dayFrom) - int(dayTo)));
    return double(diff) / nrOfDaysInMonth;
}

} // namespace hypotheek
