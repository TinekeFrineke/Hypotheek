#pragma once

#include <string>

namespace Finance {
class Bedrag;
}

namespace hypotheek {

class Percentage
{
public:
    Percentage();
    Percentage(double percentage);
    explicit Percentage(const std::string& aBedrag);

    double PercentageOf(double value) const;
    Finance::Bedrag PercentageOf(const Finance::Bedrag& value) const;

    double GetPercentage() const;
    std::string ToString() const;

    Percentage& operator=(double percentage);

private:
    double mPercentage;
};

} // namespace hypotheek
