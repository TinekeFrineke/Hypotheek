//#pragma once
//
//#include <string>
//
//#include <Utilities/Bedrag.h>
//#include <Utilities/Subject.h>
//
//namespace Hypotheek
//{
//
//class Bedrag
//    : public Subject
//{
//public:
//    explicit Bedrag(unsigned int aEuros = 0, unsigned int aCenten = 0,
//                    bool aNegative = false);
//    explicit Bedrag(const std::wstring& aBedrag);
//    bool              IsNegative() const;
//    int               GetCenten() const;
//    int               GetEuros() const;
//
//    std::wstring      ToWString() const;
//
//    Bedrag            operator-() const;
//    Bedrag& operator+=(const Bedrag& aBedrag2);
//    Bedrag& operator-=(const Bedrag& aBedrag2);
//    Bedrag& operator= (const Bedrag& aBedrag2);
//
//private:
//    Finance::Bedrag mBedrag;
//};
//
//} // namespace Hypotheek