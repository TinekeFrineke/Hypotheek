
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "IHypotheekOwner.h"

class IHypotheek;
class Inifile;

class HypotheekOwner
    : public IHypotheekOwner
{
public:
    HypotheekOwner(Inifile& inifile);
    ~HypotheekOwner() override;

    // Inherited via IHypotheekOwner
    virtual void setHypotheek(std::unique_ptr<IHypotheek> hypotheek) override;
    virtual void resetHypotheek() override;
    virtual IHypotheek* getHypotheek() const override;

    std::string GetPand() const override;
    std::vector<std::string> GetPanden() const override;
    void SetPand(const std::string& pand) override;
    void DeletePand(const std::string& pand) override;

    // Inherited via IHypotheek
    virtual Finance::Bedrag GetMaandPremie() const override;
    virtual Finance::Bedrag GetMaandPremie(const Utils::Date& month) const override;
    virtual Finance::Bedrag GetJaarPremie() const override;
    virtual Finance::Bedrag GetJaarPremie(int year) const override;
    virtual void SetHypotheekBedrag(const Finance::Bedrag& bedrag) override;
    virtual void SetStartDate(const Utils::Date& date) override;
    virtual void SetRentePercentage(const hypotheek::Percentage& jaarrente) override;

    virtual Finance::Bedrag maandRente(const Utils::Date& month) const override;
    virtual Finance::Bedrag maandAflossing(const Utils::Date& month) const override;
    virtual Finance::Bedrag maandRestSchuld(const Utils::Date& month) const override;
    virtual Finance::Bedrag jaarRente(const Utils::Date& month) const override;
    virtual Finance::Bedrag jaarAflossing(const Utils::Date& month) const override;
    virtual Finance::Bedrag jaarRestSchuld(const Utils::Date& month) const override;
    virtual void setExtraAflossing(const Utils::Date& date, const Finance::Bedrag& bedrag) override;
    virtual Finance::Bedrag initialLoan() const override;
    virtual hypotheek::Percentage interestPercentage() const override;
    virtual hypotheek::Percentage effectiveMonthlyInterest() const override;
    virtual Utils::Date StartDate() const override;

    void VulPandenUitInifile();
    void PandenToInifile();

private:
    Inifile& m_inifile;
    std::unique_ptr<IHypotheek> m_hypotheek;
    std::vector<std::string> mPanden;
    std::string mPand;
};

