#include "Percentage.h"

#include <Utilities/Bedrag.h>
#include <Utilities/strutils.h>


namespace Hypotheek
{
Percentage::Percentage()
    : mPercentage(0)
{
}
Percentage::Percentage(double percentage)
    : mPercentage(percentage)
{
}

Percentage::Percentage(const std::wstring& percentage)
    : mPercentage(Str::ToDouble(percentage))
{
}

double Percentage::PercentageOf(double value) const
{
    return value * mPercentage * 0.01;
}

Finance::Bedrag Percentage::PercentageOf(const Finance::Bedrag& value) const
{
    const double bedrag(value.ToDouble());

    return Finance::Bedrag(PercentageOf(bedrag));
}

double Percentage::GetPercentage() const
{
    return mPercentage;
}

std::wstring Percentage::ToWString() const
{
    return std::to_wstring(mPercentage);
}

Percentage& Percentage::operator=(double percentage)
{
    mPercentage = percentage;
    return *this;
}

} // namespace Hypotheek