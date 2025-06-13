
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "IHypotheekOwner.h"

class IHypotheek;
namespace utils {
class Inifile;
}

class HypotheekOwner
    : public IHypotheekOwner
{
public:
    HypotheekOwner(utils::Inifile& inifile);
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
    Finance::Bedrag GetMaandPremie() const override;
    Finance::Bedrag GetMaandPremie(const Utils::Date& month) const override;
    Finance::Bedrag GetJaarPremie() const override;
    Finance::Bedrag GetJaarPremie(int year) const override;
    void SetHypotheekBedrag(const Finance::Bedrag& bedrag) override;
    void SetStartDate(const Utils::Date& date) override;
    void SetRentePercentage(const hypotheek::Percentage& jaarrente) override;
    void SetNumberOfMonths(int numberOfMonths) override;

    Finance::Bedrag maandRente(const Utils::Date& month) const override;
    Finance::Bedrag maandAflossing(const Utils::Date& month) const override;
    Finance::Bedrag maandRestSchuld(const Utils::Date& month) const override;
    Finance::Bedrag jaarRente(const Utils::Date& month) const override;
    Finance::Bedrag jaarAflossing(const Utils::Date& month) const override;
    Finance::Bedrag jaarRestSchuld(const Utils::Date& month) const override;
    void setExtraAflossing(const Utils::Date& date, const Finance::Bedrag& bedrag) override;
    void removeExtraAflossing(const Utils::Date& date) override;
    Finance::Bedrag initialLoan() const override;
    hypotheek::Percentage interestPercentage() const override;
    hypotheek::Percentage effectiveMonthlyInterest() const override;
    Utils::Date StartDate() const override;
    int numberOfMonths() const override;
    std::map<Utils::Date, Finance::Bedrag> getExtraAflossings() const override;
    void accept(hypotheek::IVisitor& visitor) const override;

    void VulPandenUitInifile();
    void PandenToInifile();

private:
    utils::Inifile& m_inifile;
    std::unique_ptr<IHypotheek> m_hypotheek;
    std::vector<std::string> mPanden;
    std::string mPand;

};

