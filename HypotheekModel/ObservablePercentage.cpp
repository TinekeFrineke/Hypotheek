#include "ObservablePercentage.h"

#include <Utilities/strutils.h>

namespace hypotheek
{

ObservablePercentage::ObservablePercentage(double percentage)
    : mPercentage(percentage)
{
}

ObservablePercentage::ObservablePercentage(const std::wstring& percentage)
    : mPercentage(Str::ToDouble(percentage))
{
}

double ObservablePercentage::PercentageOf(double value) const
{
    return value * mPercentage * 0.01;
}

double ObservablePercentage::GetPercentage()
{
    return mPercentage;
}

std::wstring ObservablePercentage::ToWString() const { return std::to_wstring(mPercentage); }

ObservablePercentage& ObservablePercentage::operator=(double percentage)
{
    mPercentage = percentage;
    Notify();
    return *this;
}

} // namespace hypotheek