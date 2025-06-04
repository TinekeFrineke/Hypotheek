
#include "HypotheekCalculation.h"

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

std::vector<HypotheekData> CreateMonthMetrics(const IHypotheek& hypotheek)
{
    constexpr auto looptijd = 360;
    const auto loan = hypotheek.initialLoan();
    auto remainingLoan = loan;
    const auto monthlyInterest = hypotheek.effectiveMonthlyInterest();

    MonthlyDate date(hypotheek.StartDate());

    std::vector<HypotheekData> hyptheekData;
    for (auto period = 0; period < looptijd; ++period) {
        HypotheekData data;
        data.startDate = (period == 0 ? hypotheek.StartDate() : date.date());
        data.payment = hypotheek.GetMaandPremie();
        auto interest1(remainingLoan.ToDouble() * monthlyInterest.GetPercentage() / 100.0); (void)interest1;
        data.interest = Finance::Bedrag(remainingLoan.ToDouble() * monthlyInterest.GetPercentage() / 100);
        data.repayment = data.payment - data.interest;
        data.remainingDebt = remainingLoan - data.repayment;
        hyptheekData.push_back(data);

        remainingLoan -= data.repayment;
        ++date;
    }

    return hyptheekData;
}

splitPayment createSplitPayment(const hypotheekState& state)
{
    Finance::Bedrag payment = state.annuiteit;
    auto rentebedrag = Finance::Bedrag(state.restSchuld.ToDouble() * (state.rente.GetPercentage() / 12) / 100);
    auto aflossing = state.annuiteit - rentebedrag;
    return { rentebedrag, aflossing };
}

} // namespace hypotheek
