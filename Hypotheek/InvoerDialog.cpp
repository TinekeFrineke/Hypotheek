// InvoerDialog.cpp : implementation file
//

#include "pch.h"

#include "afxdialogex.h"

#include <utilities/Inifile.h>
#include <utilities/StrUtils.h>

#include "IHypotheekOwner.h"
#include "InvoerDialog.h"
#include "HypotheekApplication.h"
#include "StrConvert.h"


// InvoerDialog dialog

IMPLEMENT_DYNAMIC(InvoerDialog, CDialogEx)

InvoerDialog::InvoerDialog(std::shared_ptr<IHypotheekOwner> hypotheek, utils::Inifile& inifile, CWnd* pParent)
    : CDialogEx(IDD_INVOER_DIALOG, pParent)
    , m_hypotheek(hypotheek)
    , mInifile(inifile)
{
}

InvoerDialog::~InvoerDialog()
{
}

BOOL InvoerDialog::OnInitDialog()
{
    return CDialogEx::OnInitDialog();
}

void InvoerDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
    __super::OnShowWindow(bShow, nStatus);

    VulDialoog();
}

void InvoerDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_KOOPSOM_EDIT, mKoopsomEdit);
    DDX_Control(pDX, IDC_TAXATIE_EDIT, mTaxatieEdit);
    DDX_Control(pDX, IDC_ING_EDIT, mIngEdit);
    DDX_Control(pDX, IDC_RIEKS_EDIT, mRieksEdit);
    DDX_Control(pDX, IDC_NHG_EDIT, mNhgEdit);
    DDX_Control(pDX, IDC_OVERIG_EDIT, mKoopsomOverigen);
    DDX_Control(pDX, IDC_KOSTEN_KOPER_TOTAAL_EDIT, mKoopsomTotaal);
    DDX_Control(pDX, IDC_NATASJA_EIGEN_GELD_EDIT, mNatasjaEigenGeld);
    DDX_Control(pDX, IDC_LENEN_EDIT, mLenen);
    DDX_Control(pDX, IDC_NOTARIS_EDIT, mNotarisEdit);
    DDX_Control(pDX, IDC_PAND_COMBO, mPandCombo);
}


BEGIN_MESSAGE_MAP(InvoerDialog, CDialogEx)
    ON_EN_CHANGE(IDC_KOOPSOM_EDIT, &InvoerDialog::OnEnChangeKoopsomEdit)
    ON_EN_CHANGE(IDC_TAXATIE_EDIT, &InvoerDialog::OnEnChangeTaxatieEdit)
    ON_EN_CHANGE(IDC_ING_EDIT, &InvoerDialog::OnEnChangeIngEdit)
    ON_EN_CHANGE(IDC_RIEKS_EDIT, &InvoerDialog::OnEnChangeRieksEdit)
    ON_EN_CHANGE(IDC_NHG_EDIT, &InvoerDialog::OnEnChangeNhgEdit)
    ON_EN_CHANGE(IDC_OVERIG_EDIT, &InvoerDialog::OnEnChangeOverigEdit)
    ON_EN_CHANGE(IDC_KOSTEN_KOPER_TOTAAL_EDIT, &InvoerDialog::OnEnChangeKostenKoperTotaalEdit)
    ON_EN_CHANGE(IDC_NATASJA_EIGEN_GELD_EDIT, &InvoerDialog::OnEnChangeNatasjaEigenGeldEdit)
    ON_WM_SHOWWINDOW()
    ON_EN_CHANGE(IDC_NOTARIS_EDIT, &InvoerDialog::OnEnChangeNotarisEdit)
    ON_BN_CLICKED(IDC_SAVE_BUTTON, &InvoerDialog::OnBnClickedSaveButton)
    ON_BN_CLICKED(IDC_DELETE_BUTTON, &InvoerDialog::OnBnClickedDeleteButton)
END_MESSAGE_MAP()


// InvoerDialog message handlers

std::string InvoerDialog::GetPand() const
{
    return m_hypotheek->GetPand();
}

void InvoerDialog::HerberekenKoopsomTotaal()
{
    mKoopsomTotaal.SetValue(mKoopsomEdit.GetValue()
                            + mTaxatieEdit.GetValue()
                            + mNhgEdit.GetValue()
                            + mNotarisEdit.GetValue()
                            + mKoopsomOverigen.GetValue());
}

void InvoerDialog::HerberekenLening()
{
    mLenen.SetValue(mKoopsomTotaal.GetValue() - mNatasjaEigenGeld.GetValue());
    mInifile.set(GetPand(), u8"lening", std::to_string(mLenen.GetValue()));
}

void InvoerDialog::VulPandCombo()
{
    mPandCombo.ResetContent();
    for (auto pand : m_hypotheek->GetPanden())
        mPandCombo.AddString(StrConvert::Utf8ToUtf16(pand).c_str());
}

void InvoerDialog::VulDialoog()
{
    VulPandCombo();

    mPandCombo.SelectString(0, StrConvert::Utf8ToUtf16(m_hypotheek->GetPand()).c_str());

    mKoopsomEdit.SetValue(Str::ToDouble(mInifile.get(GetPand(), u8"koopsom")));
    mTaxatieEdit.SetValue(Str::ToDouble(mInifile.get(u8"invoer", u8"taxatie")));
    mIngEdit.SetValue(Str::ToDouble(mInifile.get(u8"invoer", u8"ingadvies")));
    mRieksEdit.SetValue(Str::ToDouble(mInifile.get(u8"invoer", u8"rieks")));
    mNotarisEdit.SetValue(Str::ToDouble(mInifile.get(u8"invoer", u8"notaris")));
    mNhgEdit.SetValue(Str::ToDouble(mInifile.get(GetPand(), u8"nhg")));
    mKoopsomOverigen.SetValue(Str::ToDouble(mInifile.get(GetPand(), u8"overige")));
    mNatasjaEigenGeld.SetValue(Str::ToDouble(mInifile.get(u8"invoer", u8"natasja")));
}

void InvoerDialog::BewaarDialoog()
{
    mInifile.set(GetPand(), u8"koopsom", std::to_string(mKoopsomEdit.GetValue()));
    mInifile.set(GetPand(), u8"nhg", std::to_string(mNhgEdit.GetValue()));
    mInifile.set(GetPand(), u8"overige", std::to_string(mKoopsomOverigen.GetValue()));
}


void InvoerDialog::OnEnChangeKoopsomEdit()
{
    mInifile.set(GetPand(), u8"koopsom", std::to_string(mKoopsomEdit.GetValue()));
    HerberekenKoopsomTotaal();
}


void InvoerDialog::OnEnChangeTaxatieEdit()
{
    mInifile.set(u8"invoer", u8"taxatie", std::to_string(mTaxatieEdit.GetValue()));
    HerberekenKoopsomTotaal();
}


void InvoerDialog::OnEnChangeIngEdit()
{
    mInifile.set(u8"invoer", u8"ingadvies", std::to_string(mIngEdit.GetValue()));
    HerberekenKoopsomTotaal();
}


void InvoerDialog::OnEnChangeRieksEdit()
{
    mInifile.set(u8"invoer", u8"rieks", std::to_string(mRieksEdit.GetValue()));
}


void InvoerDialog::OnEnChangeNhgEdit()
{
    mInifile.set(GetPand(), u8"nhg", std::to_string(mNhgEdit.GetValue()));
    HerberekenKoopsomTotaal();
}


void InvoerDialog::OnEnChangeOverigEdit()
{
    mInifile.set(GetPand(), u8"overige", std::to_string(mKoopsomOverigen.GetValue()));
    HerberekenKoopsomTotaal();
}


void InvoerDialog::OnEnChangeKostenKoperTotaalEdit()
{
    HerberekenLening();
}


void InvoerDialog::OnEnChangeNatasjaEigenGeldEdit()
{
    mInifile.set(u8"invoer", u8"natasja", std::to_string(mNatasjaEigenGeld.GetValue()));
    HerberekenLening();
}


void InvoerDialog::OnEnChangeNotarisEdit()
{
    mInifile.set(u8"invoer", u8"notaris", std::to_string(mNotarisEdit.GetValue()));
    HerberekenKoopsomTotaal();
}


void InvoerDialog::OnBnClickedSaveButton()
{
    CString pand;
    mPandCombo.GetWindowText(pand);
    m_hypotheek->SetPand(StrConvert::Utf16ToUtf8((const wchar_t*)pand));
    VulDialoog();
}


void InvoerDialog::OnBnClickedDeleteButton()
{
    CString pand;
    mPandCombo.GetWindowText(pand);
    m_hypotheek->DeletePand(StrConvert::Utf16ToUtf8((const wchar_t*)pand));
}
