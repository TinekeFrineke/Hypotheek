
#include "HypotheekOwner.h"

#include <Utilities/Bedrag.h>
#include <Utilities/Inifile.h>

namespace {
const std::wstring unspecifiedPand(L"<unspecified>");
}


HypotheekOwner::HypotheekOwner(Inifile& inifile)
    : m_inifile(inifile)
{
}

HypotheekOwner::~HypotheekOwner() = default;

void HypotheekOwner::setHypotheek(std::unique_ptr<IHypotheek> hypotheek)
{
    m_hypotheek = std::move(hypotheek);
}

void HypotheekOwner::resetHypotheek()
{
    m_hypotheek.reset();
}

IHypotheek* HypotheekOwner::getHypotheek() const
{
    return m_hypotheek.get();
}

std::wstring HypotheekOwner::GetPand() const
{
    return mPand;
}

std::vector<std::wstring> HypotheekOwner::GetPanden() const
{
    return mPanden;
}

void HypotheekOwner::SetPand(const std::wstring& pand)
{
    mPand = pand;
    auto pandIter(std::find(mPanden.begin(), mPanden.end(), pand));
    if (pandIter == mPanden.end())
        mPanden.emplace_back(pand);

    PandenToInifile();
}

void HypotheekOwner::DeletePand(const std::wstring& pand)
{
    if (pand == unspecifiedPand)
        return;

    auto pandIter(std::find(mPanden.begin(), mPanden.end(), pand));
    if (pandIter != mPanden.end()) {
        if (pand == mPand)
            if (pandIter != mPanden.begin())
                mPand = *(pandIter - 1);
            else if (pandIter != mPanden.end() - 1)
                mPand = *(pandIter + 1);
            else
                mPand = unspecifiedPand;
        mPanden.erase(pandIter);
    }

    PandenToInifile();
}

void HypotheekOwner::VulPandenUitInifile()
{
    mPand = m_inifile[L"panden"][L"huidigpand"];
    if (mPand.empty())
        mPand = unspecifiedPand;

    for (auto pand : m_inifile[L"panden"])
        mPanden.push_back(pand.second);

    auto pandIter(std::find(mPanden.begin(), mPanden.end(), unspecifiedPand));
    if (pandIter == mPanden.end())
        mPanden.insert(mPanden.begin(), unspecifiedPand);
}

void HypotheekOwner::PandenToInifile()
{
    m_inifile[L"panden"].Clear();
    for (size_t i = 0; i < mPanden.size(); ++i)
        m_inifile[L"panden"][L"pand" + std::to_wstring(i)] = mPanden[i];

    m_inifile[L"panden"][L"huidigpand"] = mPand;
}

Finance::Bedrag HypotheekOwner::GetMaandPremie() const
{
    return m_hypotheek->GetMaandPremie();
}

Finance::Bedrag HypotheekOwner::GetMaandPremie(const Utils::Date& month) const
{
    return m_hypotheek->GetMaandPremie(month);
}

Finance::Bedrag HypotheekOwner::GetJaarPremie() const
{
    return m_hypotheek->GetJaarPremie();
}

Finance::Bedrag HypotheekOwner::GetJaarPremie(int year) const
{
    return m_hypotheek->GetJaarPremie(year);
}

void HypotheekOwner::SetHypotheekBedrag(const Finance::Bedrag& bedrag)
{
    m_hypotheek->SetHypotheekBedrag(bedrag);
}

void HypotheekOwner::SetStartDate(const Utils::Date& date)
{
    m_hypotheek->SetStartDate(date);
}

void HypotheekOwner::SetRentePercentage(const Hypotheek::Percentage& jaarrente)
{
    m_hypotheek->SetRentePercentage(jaarrente);
}

