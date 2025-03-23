#pragma once

#include <memory>

namespace Finance {
class Bedrag;
}

namespace hypotheek {
class Percentage;
}

namespace Utils {
class Date;
}

class IHypotheek
{
public:
    virtual ~IHypotheek() = default;

    virtual Finance::Bedrag initialLoan() const = 0;
    virtual hypotheek::Percentage interestPercentage() const = 0;
    virtual hypotheek::Percentage effectiveMonthlyInterest() const = 0;
    virtual Utils::Date StartDate() const = 0;

    virtual Finance::Bedrag GetMaandPremie() const = 0;
    virtual Finance::Bedrag GetMaandPremie(const Utils::Date& month) const = 0;
    virtual Finance::Bedrag GetJaarPremie() const = 0;
    virtual Finance::Bedrag GetJaarPremie(int year) const = 0;

    virtual Finance::Bedrag maandRente(const Utils::Date& month) const = 0;
    virtual Finance::Bedrag maandAflossing(const Utils::Date& month) const = 0;
    virtual Finance::Bedrag maandRestSchuld(const Utils::Date& month) const = 0;

    virtual Finance::Bedrag jaarRente(const Utils::Date  & month) const = 0;
    virtual Finance::Bedrag jaarAflossing(const Utils::Date& month) const = 0;
    virtual Finance::Bedrag jaarRestSchuld(const Utils::Date& month) const = 0;

    virtual void SetHypotheekBedrag(const Finance::Bedrag& bedrag) = 0;
    virtual void SetStartDate(const Utils::Date& date) = 0;
    virtual void SetRentePercentage(const hypotheek::Percentage& jaarrente) = 0;
    virtual void setExtraAflossing(const Utils::Date& date, const Finance::Bedrag& bedrag) = 0;
};

namespace hypotheek
{

enum class HYPOTHEEK_VORM;

std::unique_ptr<IHypotheek> CreateHypotheek(HYPOTHEEK_VORM vorm);

}