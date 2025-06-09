
#include "HypotheekOwner.h"

#include <utilities/Bedrag.h>
#include <utilities/Date.h>
#include <utilities/Inifile.h>
#include <HypotheekModel/Percentage.h>

namespace {
const std::string unspecifiedPand(u8"<unspecified>");
}


HypotheekOwner::HypotheekOwner(utils::Inifile& inifile)
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

std::string HypotheekOwner::GetPand() const
{
    return mPand;
}

std::vector<std::string> HypotheekOwner::GetPanden() const
{
    return mPanden;
}

void HypotheekOwner::SetPand(const std::string& pand)
{
    mPand = pand;
    auto pandIter(std::find(mPanden.begin(), mPanden.end(), pand));
    if (pandIter == mPanden.end())
        mPanden.emplace_back(pand);

    PandenToInifile();
}

void HypotheekOwner::DeletePand(const std::string& pand)
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
    try {
        mPand = m_inifile.get(u8"panden", u8"huidigpand");
    }
    catch (std::exception& /*ex*/) {
        mPand = unspecifiedPand;
    }

    auto sections(m_inifile.getSections());
    auto found = std::find(sections.begin(), sections.end(), u8"panden");
    if (found != sections.end()) {
        mPanden.clear();
        const auto keys = m_inifile.getKeys(*found);
        for (auto key : keys)
            if (key.find("pand") == 0)
                mPanden.push_back(m_inifile.get(u8"panden", key));
    }

    auto pandIter(std::find(mPanden.begin(), mPanden.end(), unspecifiedPand));
    if (pandIter == mPanden.end())
        mPanden.insert(mPanden.begin(), unspecifiedPand);
}

void HypotheekOwner::PandenToInifile()
{
    m_inifile.erase(u8"panden");
    for (size_t i = 0; i < mPanden.size(); ++i)
        m_inifile.set(u8"panden", u8"pand" + std::to_string(i), mPanden[i]);

    m_inifile.set(u8"panden", u8"huidigpand", mPand);
}

std::map<Utils::Date, Finance::Bedrag> HypotheekOwner::getExtraAflossings() const
{
    return m_hypotheek->getExtraAflossings();
}

void HypotheekOwner::accept(hypotheek::IVisitor& visitor) const
{
    m_hypotheek->accept(visitor);
}

Finance::Bedrag HypotheekOwner::initialLoan() const
{
    return m_hypotheek->initialLoan();
}

hypotheek::Percentage HypotheekOwner::interestPercentage() const
{
    return m_hypotheek->interestPercentage();
}

hypotheek::Percentage HypotheekOwner::effectiveMonthlyInterest() const
{
    return m_hypotheek->effectiveMonthlyInterest();
}

Utils::Date HypotheekOwner::StartDate() const
{
    return m_hypotheek->StartDate();
}

Finance::Bedrag HypotheekOwner::maandRente(const Utils::Date& month) const
{
    return m_hypotheek->maandRente(month);
}

Finance::Bedrag HypotheekOwner::maandAflossing(const Utils::Date& month) const
{
    return m_hypotheek->maandAflossing(month);
}

Finance::Bedrag HypotheekOwner::maandRestSchuld(const Utils::Date& month) const
{
    return m_hypotheek->maandRestSchuld(month);
}

Finance::Bedrag HypotheekOwner::jaarRente(const Utils::Date& month) const
{
    return m_hypotheek->jaarRente(month);
}

Finance::Bedrag HypotheekOwner::jaarAflossing(const Utils::Date& month) const
{
    return m_hypotheek->jaarAflossing(month);
}

Finance::Bedrag HypotheekOwner::jaarRestSchuld(const Utils::Date& month) const
{
    return m_hypotheek->jaarRestSchuld(month);
}

void HypotheekOwner::setExtraAflossing(const Utils::Date& date, const Finance::Bedrag& bedrag)
{
    m_hypotheek->setExtraAflossing(date, bedrag);
}

void HypotheekOwner::removeExtraAflossing(const Utils::Date& date)
{
    m_hypotheek->removeExtraAflossing(date);
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

void HypotheekOwner::SetRentePercentage(const hypotheek::Percentage& jaarrente)
{
    m_hypotheek->SetRentePercentage(jaarrente);
}

