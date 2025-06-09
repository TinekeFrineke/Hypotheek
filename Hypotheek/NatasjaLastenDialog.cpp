// NatasjaLastenDialog.cpp : implementation file
//

#include "pch.h"

#include <HypotheekModel/HypotheekDefinitions.h>
#include <HypotheekModel/IHypotheek.h>
#include <HypotheekModel/Percentage.h>
#include <utilities/Date.h>
#include <utilities/Inifile.h>
#include <utilities/strutils.h>

#include "afxdialogex.h"
#include "IHypotheekOwner.h"
#include "NatasjaLastenDialog.h"
#include "StrConvert.h"


// NatasjaLastenDialog dialog

IMPLEMENT_DYNAMIC(NatasjaLastenDialog, CDialog)

NatasjaLastenDialog::NatasjaLastenDialog(std::shared_ptr<IHypotheekOwner> owner, utils::Inifile& inifile, CWnd* pParent /*=nullptr*/)
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
        if (mInifile.get(u8"natasja", u8"vorm") == u8"Annuitair") {
            mRadioAnnuitair.SetCheck(BST_CHECKED);
            m_hypotheek->setHypotheek(hypotheek::CreateHypotheek(hypotheek::HYPOTHEEK_VORM::Annuitair));
        }
        else {
            mRadioAflossingsvrij.SetCheck(BST_CHECKED);
            m_hypotheek->setHypotheek(hypotheek::CreateHypotheek(hypotheek::HYPOTHEEK_VORM::Aflossingsvrij));
        }

        mLening.SetValue(Str::ToDouble(mInifile.get(m_hypotheek->GetPand(), u8"lening")));
        std::string dateString = mInifile.get(u8"natasja", u8"start");
        mStartDatum.SetWindowText(StrConvert::Utf8ToUtf16(dateString).c_str());
        Utils::Date startDate(Utils::Today());
        try {
            startDate = Utils::ToDate(dateString);
        }
        catch (...) {
        }
        mRentePercentage.SetValue(Str::ToDouble(mInifile.get(u8"natasja", u8"rentepercentage")));

        mSchenkingen.SetValue(Str::ToDouble(mInifile.get(u8"natasja", u8"schenkingen")));
        m_hypotheek->SetHypotheekBedrag(Finance::Bedrag(mLening.GetValue()));
        m_hypotheek->SetRentePercentage(mRentePercentage.GetValue());
        m_hypotheek->SetStartDate(startDate);
        mJaarrente.SetValue(m_hypotheek->GetJaarPremie().ToDouble());

        mVve.SetValue(Str::ToDouble(mInifile.get(m_hypotheek->GetPand(), u8"vve")));
        mErfpacht.SetValue(Str::ToDouble(mInifile.get(m_hypotheek->GetPand(), u8"erfpacht")));
        mOpstalVerzekeringEdit.SetValue(Str::ToDouble(mInifile.get(u8"natasja", u8"opstal")));
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
    mInifile.set(u8"natasja", u8"rentepercentage", std::to_string(mRentePercentage.GetValue()));
    m_hypotheek->SetRentePercentage(mRentePercentage.GetValue());
    mJaarrente.SetValue(m_hypotheek->GetJaarPremie().ToDouble());
}


void NatasjaLastenDialog::OnEnChangeSchenkingenEdit()
{
    mInifile.set(u8"natasja", u8"schenkingen", std::to_string(mSchenkingen.GetValue()));
    mRestJaarrente.SetValue(mJaarrente.GetValue() - mSchenkingen.GetValue());
}


void NatasjaLastenDialog::OnEnChangeRestJaarrenteEdit()
{
    mMaandrente.SetValue(mRestJaarrente.GetValue() / 12);
    BerekenTotaleLasten();
}

void NatasjaLastenDialog::OnEnChangeEditVve()
{
    mInifile.set(m_hypotheek->GetPand(), u8"vve", std::to_string(mVve.GetValue()));
    BerekenTotaleLasten();
}


void NatasjaLastenDialog::OnEnChangeErfpachtEdit()
{
    mInifile.set(m_hypotheek->GetPand(), u8"erfpacht", std::to_string(mErfpacht.GetValue()));
    BerekenTotaleLasten();
}

void NatasjaLastenDialog::OnEnChangeOpstalverzekeringEdit()
{
    mInifile.set(u8"natasja", u8"opstal", std::to_string(mOpstalVerzekeringEdit.GetValue()));
    BerekenTotaleLasten();
}


void NatasjaLastenDialog::OnEnChangeJaarrenteEdit()
{
    mRestJaarrente.SetValue(mJaarrente.GetValue() - mSchenkingen.GetValue());
}


void NatasjaLastenDialog::OnBnClickedRadioAnnuitair()
{
    mInifile.set(u8"natasja", u8"vorm", u8"Annuitair");
    m_hypotheek->setHypotheek(hypotheek::CreateHypotheek(hypotheek::HYPOTHEEK_VORM::Annuitair));
    m_hypotheek->SetHypotheekBedrag(Finance::Bedrag(mLening.GetValue()));
    m_hypotheek->SetRentePercentage(mRentePercentage.GetValue());

    mJaarrente.SetValue(m_hypotheek->GetJaarPremie().ToDouble());
}


void NatasjaLastenDialog::OnBnClickedRadioAflossingsvrij()
{
    mInifile.set(u8"natasja", u8"vorm", u8"Aflossingsvrij");
    m_hypotheek->setHypotheek(hypotheek::CreateHypotheek(hypotheek::HYPOTHEEK_VORM::Aflossingsvrij));
    m_hypotheek->SetHypotheekBedrag(Finance::Bedrag(mLening.GetValue()));
    m_hypotheek->SetRentePercentage(mRentePercentage.GetValue());

    mJaarrente.SetValue(m_hypotheek->GetJaarPremie().ToDouble());
}


void NatasjaLastenDialog::OnEnKillfocusEditStartdatum()
{
    CString dateString;
    mStartDatum.GetWindowText(dateString);
    mInifile.set(u8"natasja", u8"start", StrConvert::Utf16ToUtf8((wchar_t*)dateString.GetBuffer()));
    try {
        Utils::Date startDate(Utils::ToDate(StrConvert::Utf16ToUtf8((wchar_t*)dateString.GetBuffer())));
        m_hypotheek->SetStartDate(startDate);
    }
    catch (...) {

    }
}
