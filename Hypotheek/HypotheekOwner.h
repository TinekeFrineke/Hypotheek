
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

    std::wstring GetPand() const override;
    std::vector<std::wstring> GetPanden() const override;
    void SetPand(const std::wstring& pand) override;
    void DeletePand(const std::wstring& pand) override;

    // Inherited via IHypotheek
    virtual Finance::Bedrag GetMaandPremie() const override;
    virtual Finance::Bedrag GetMaandPremie(const Utils::Date& month) const override;
    virtual Finance::Bedrag GetJaarPremie() const override;
    virtual Finance::Bedrag GetJaarPremie(int year) const override;
    virtual void SetHypotheekBedrag(const Finance::Bedrag& bedrag) override;
    virtual void SetStartDate(const Utils::Date& date) override;
    virtual void SetRentePercentage(const Hypotheek::Percentage& jaarrente) override;

    void VulPandenUitInifile();
    void PandenToInifile();

private:
    Inifile& m_inifile;
    std::unique_ptr<IHypotheek> m_hypotheek;
    std::vector<std::wstring> mPanden;
    std::wstring mPand;

};

