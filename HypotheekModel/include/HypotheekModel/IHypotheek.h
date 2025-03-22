#pragma once

#include <memory>

namespace Finance {
class Bedrag;
}

namespace Hypotheek {
class Percentage;
}

namespace Utils {
class Date;
}

class IHypotheek
{
public:
    virtual ~IHypotheek() = default;

    virtual Finance::Bedrag GetMaandPremie() const = 0;
    virtual Finance::Bedrag GetMaandPremie(const Utils::Date& month) const = 0;
    virtual Finance::Bedrag GetJaarPremie() const = 0;
    virtual Finance::Bedrag GetJaarPremie(int year) const = 0;

    virtual void SetHypotheekBedrag(const Finance::Bedrag& bedrag) = 0;
    virtual void SetStartDate(const Utils::Date& date) = 0;
    virtual void SetRentePercentage(const Hypotheek::Percentage& jaarrente) = 0;
};

namespace Hypotheek
{

enum class HYPOTHEEK_VORM;

std::unique_ptr<IHypotheek> CreateHypotheek(HYPOTHEEK_VORM vorm);

}