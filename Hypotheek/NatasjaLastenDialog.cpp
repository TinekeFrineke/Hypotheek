// NatasjaLastenDialog.cpp : implementation file
//

#include "pch.h"

#include <HypotheekModel/HypotheekDefinitions.h>
#include <HypotheekModel/IHypotheek.h>
#include <HypotheekModel/Percentage.h>
#include <Utilities/Date.h>
#include <Utilities/Inifile.h>
#include <Utilities/strutils.h>

#include "afxdialogex.h"
#include "IHypotheekOwner.h"
#include "NatasjaLastenDialog.h"


// NatasjaLastenDialog dialog

IMPLEMENT_DYNAMIC(NatasjaLastenDialog, CDialog)

NatasjaLastenDialog::NatasjaLastenDialog(std::shared_ptr<IHypotheekOwner> owner, Inifile& inifile, CWnd* pParent /*=nullptr*/)
    : CDialog(IDD_LASTEN_NATASJA_DIALOG, pParent)
    , m_hypotheek(owner)
    , mInifile(inifile)
{
}

NatasjaLastenDialog::~NatasjaLastenDialog()
{
}


void NatasjaLastenDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
    __super::OnShowWindow(bShow, nStatus);

    if (bShow) {
        if (mInifile[L"natasja"][L"vorm"] == L"Annuitair") {
            mRadioAnnuitair.SetCheck(BST_CHECKED);
            m_hypotheek->setHypotheek(hypotheek::CreateHypotheek(hypotheek::HYPOTHEEK_VORM::Annuitair));
        }
        else {
            mRadioAflossingsvrij.SetCheck(BST_CHECKED);
            m_hypotheek->setHypotheek(hypotheek::CreateHypotheek(hypotheek::HYPOTHEEK_VORM::Aflossingsvrij));
        }

        mLening.SetValue(Str::ToDouble(mInifile[m_hypotheek->GetPand()][L"lening"]));
        std::wstring dateString = mInifile[L"natasja"][L"start"];
        mStartDatum.SetWindowText(dateString.c_str());
        Utils::Date startDate(Utils::Now());
        try {
            startDate = Utils::ToDate(dateString);
        }
        catch (...) {
        }
        mRentePercentage.SetValue(Str::ToDouble(mInifile[L"natasja"][L"rentepercentage"]));

        mSchenkingen.SetValue(Str::ToDouble(mInifile[L"natasja"][L"schenkingen"]));
        m_hypotheek->SetHypotheekBedrag(Finance::Bedrag(mLening.GetValue()));
        m_hypotheek->SetRentePercentage(mRentePercentage.GetValue());
        m_hypotheek->SetStartDate(startDate);
        mJaarrente.SetValue(m_hypotheek->GetJaarPremie().ToDouble());

        mVve.SetValue(Str::ToDouble(mInifile[m_hypotheek->GetPand()][L"vve"]));
        mErfpacht.SetValue(Str::ToDouble(mInifile[m_hypotheek->GetPand()][L"erfpacht"]));
        mOpstalVerzekeringEdit.SetValue(Str::ToDouble(mInifile[L"natasja"][L"opstal"]));
    }
}

void NatasjaLastenDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LENING_EDIT, mLening);
    DDX_Control(pDX, IDC_RENTE_PERCENTAGE_EDIT, mRentePercentage);
    DDX_Control(pDX, IDC_JAARRENTE_EDIT, mJaarrente);
    DDX_Control(pDX, IDC_SCHENKINGEN_EDIT, mSchenkingen);
    DDX_Control(pDX, IDC_REST_JAARRENTE_EDIT, mRestJaarrente);
    DDX_Control(pDX, IDC_MAANDRENTE_EDIT, mMaandrente);
    DDX_Control(pDX, IDC_EDIT_VVE, mVve);
    DDX_Control(pDX, IDC_ERFPACHT_EDIT, mErfpacht);
    DDX_Control(pDX, IDC_TOTALE_LASTEN_EDIT, mTotaleLasten);
    DDX_Control(pDX, IDC_OPSTALVERZEKERING_EDIT, mOpstalVerzekeringEdit);
    DDX_Control(pDX, IDC_RADIO_ANNUITAIR, mRadioAnnuitair);
    DDX_Control(pDX, IDC_RADIO_AFLOSSINGSVRIJ, mRadioAflossingsvrij);
    DDX_Control(pDX, IDC_EDIT_STARTDATUM, mStartDatum);
}

void NatasjaLastenDialog::BerekenTotaleLasten()
{
    mTotaleLasten.SetValue(mMaandrente.GetValue() + mVve.GetValue() + mErfpacht.GetValue() + mOpstalVerzekeringEdit.GetValue());
}


BEGIN_MESSAGE_MAP(NatasjaLastenDialog, CDialog)
    ON_EN_CHANGE(IDC_RENTE_PERCENTAGE_EDIT, &NatasjaLastenDialog::OnEnChangeRentePercentageEdit)
    ON_EN_CHANGE(IDC_SCHENKINGEN_EDIT, &NatasjaLastenDialog::OnEnChangeSchenkingenEdit)
    ON_EN_CHANGE(IDC_EDIT_VVE, &NatasjaLastenDialog::OnEnChangeEditVve)
    ON_EN_CHANGE(IDC_ERFPACHT_EDIT, &NatasjaLastenDialog::OnEnChangeErfpachtEdit)
    ON_WM_SHOWWINDOW()
    ON_EN_CHANGE(IDC_REST_JAARRENTE_EDIT, &NatasjaLastenDialog::OnEnChangeRestJaarrenteEdit)
    ON_EN_CHANGE(IDC_OPSTALVERZEKERING_EDIT, &NatasjaLastenDialog::OnEnChangeOpstalverzekeringEdit)
    ON_EN_CHANGE(IDC_JAARRENTE_EDIT, &NatasjaLastenDialog::OnEnChangeJaarrenteEdit)
    ON_BN_CLICKED(IDC_RADIO_ANNUITAIR, &NatasjaLastenDialog::OnBnClickedRadioAnnuitair)
    ON_BN_CLICKED(IDC_RADIO_AFLOSSINGSVRIJ, &NatasjaLastenDialog::OnBnClickedRadioAflossingsvrij)
    ON_EN_KILLFOCUS(IDC_EDIT_STARTDATUM, &NatasjaLastenDialog::OnEnKillfocusEditStartdatum)
END_MESSAGE_MAP()


// NatasjaLastenDialog message handlers


void NatasjaLastenDialog::OnEnChangeRentePercentageEdit()
{
    mInifile[L"natasja"][L"rentepercentage"] = std::to_wstring(mRentePercentage.GetValue());
    m_hypotheek->SetRentePercentage(mRentePercentage.GetValue());
    mJaarrente.SetValue(m_hypotheek->GetJaarPremie().ToDouble());
}


void NatasjaLastenDialog::OnEnChangeSchenkingenEdit()
{
    mInifile[L"natasja"][L"schenkingen"] = std::to_wstring(mSchenkingen.GetValue());
    mRestJaarrente.SetValue(mJaarrente.GetValue() - mSchenkingen.GetValue());
}


void NatasjaLastenDialog::OnEnChangeRestJaarrenteEdit()
{
    mMaandrente.SetValue(mRestJaarrente.GetValue() / 12);
    BerekenTotaleLasten();
}

void NatasjaLastenDialog::OnEnChangeEditVve()
{
    mInifile[m_hypotheek->GetPand()][L"vve"] = std::to_wstring(mVve.GetValue());
    BerekenTotaleLasten();
}


void NatasjaLastenDialog::OnEnChangeErfpachtEdit()
{
    mInifile[m_hypotheek->GetPand()][L"erfpacht"] = std::to_wstring(mErfpacht.GetValue());
    BerekenTotaleLasten();
}

void NatasjaLastenDialog::OnEnChangeOpstalverzekeringEdit()
{
    mInifile[L"natasja"][L"opstal"] = std::to_wstring(mOpstalVerzekeringEdit.GetValue());
    BerekenTotaleLasten();
}


void NatasjaLastenDialog::OnEnChangeJaarrenteEdit()
{
    mRestJaarrente.SetValue(mJaarrente.GetValue() - mSchenkingen.GetValue());
}


void NatasjaLastenDialog::OnBnClickedRadioAnnuitair()
{
    mInifile[L"natasja"][L"vorm"] = L"Annuitair";
    m_hypotheek->setHypotheek(hypotheek::CreateHypotheek(hypotheek::HYPOTHEEK_VORM::Annuitair));
    m_hypotheek->SetHypotheekBedrag(Finance::Bedrag(mLening.GetValue()));
    m_hypotheek->SetRentePercentage(mRentePercentage.GetValue());

    mJaarrente.SetValue(m_hypotheek->GetJaarPremie().ToDouble());
}


void NatasjaLastenDialog::OnBnClickedRadioAflossingsvrij()
{
    mInifile[L"natasja"][L"vorm"] = L"Aflossingsvrij";
    m_hypotheek->setHypotheek(hypotheek::CreateHypotheek(hypotheek::HYPOTHEEK_VORM::Aflossingsvrij));
    m_hypotheek->SetHypotheekBedrag(Finance::Bedrag(mLening.GetValue()));
    m_hypotheek->SetRentePercentage(mRentePercentage.GetValue());

    mJaarrente.SetValue(m_hypotheek->GetJaarPremie().ToDouble());
}


void NatasjaLastenDialog::OnEnKillfocusEditStartdatum()
{
    CString dateString;
    mStartDatum.GetWindowText(dateString);
    mInifile[L"natasja"][L"start"] = (wchar_t*)dateString.GetBuffer();
    try {
        Utils::Date startDate(Utils::ToDate((wchar_t*)dateString.GetBuffer()));
        m_hypotheek->SetStartDate(startDate);
    }
    catch (...) {

    }
}
