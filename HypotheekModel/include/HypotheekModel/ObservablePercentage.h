#pragma once

#include <string>

#include <Utilities/Bedrag.h>
#include <Utilities/Subject.h>

namespace Hypotheek
{

class ObservablePercentage
    : public Subject
{
public:
    // e.g. 4.5 means 4.5%
    explicit ObservablePercentage(double percentage);
    explicit ObservablePercentage(const std::wstring& aBedrag);

    double PercentageOf(double value) const;

    double            GetPercentage();
    std::wstring      ToWString() const;

    ObservablePercentage& operator=(double percentage);

private:
    double mPercentage;
};

} // namespace Hypotheek