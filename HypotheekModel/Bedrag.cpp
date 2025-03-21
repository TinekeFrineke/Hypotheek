//#include "Bedrag.h"
//
//namespace Hypotheek
//{
//
//Bedrag::Bedrag(unsigned int aEuros, unsigned int aCenten,
//               bool aNegative)
//    : mBedrag(aEuros, aCenten, aNegative)
//{
//}
//
//Bedrag::Bedrag(const std::wstring& aBedrag)
//    : mBedrag(aBedrag)
//{
//}
//
//bool Bedrag::IsNegative() const { return mBedrag.IsNegative(); }
//int  Bedrag::GetCenten() const { return mBedrag.GetCenten(); }
//int  Bedrag::GetEuros() const { return mBedrag.GetEuros(); }
//
//std::wstring Bedrag::ToWString() const { return mBedrag.ToTString(); }
//
//Bedrag Bedrag::operator-() const { mBedrag.operator-(); return *this; }
//Bedrag& Bedrag::operator+=(const Bedrag& aBedrag2)
//{
//    mBedrag += aBedrag2.mBedrag;
//    Notify();
//    return *this;
//}
//
//Bedrag& Bedrag::operator-=(const Bedrag& aBedrag2)
//{
//    mBedrag -= aBedrag2.mBedrag;
//    Notify();
//    return *this;
//}
//
//Bedrag& Bedrag::operator=(const Bedrag& aBedrag2)
//{
//    mBedrag = aBedrag2.mBedrag;
//    Notify();
//    return *this;
//}
//
//} // namespace Hypotheek