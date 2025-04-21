#include "Percentage.h"

#include <Utilities/Bedrag.h>
#include <Utilities/strutils.h>


namespace hypotheek
{
Percentage::Percentage()
    : mPercentage(0)
{
}
Percentage::Percentage(double percentage)
    : mPercentage(percentage)
{
}

Percentage::Percentage(const std::string& percentage)
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

std::string Percentage::ToString() const
{
    return std::to_string(mPercentage);
}

Percentage& Percentage::operator=(double percentage)
{
    mPercentage = percentage;
    return *this;
}

} // namespace hypotheek