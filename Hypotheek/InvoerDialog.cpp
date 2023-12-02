// InvoerDialog.cpp : implementation file
//

#include "pch.h"

#include "InvoerDialog.h"

#include "Hypotheek.h"
#include "afxdialogex.h"

#include <Utilities/Inifile.h>


// InvoerDialog dialog

IMPLEMENT_DYNAMIC(InvoerDialog, CDialogEx)

InvoerDialog::InvoerDialog(HypotheekApplication& app, Inifile& inifile, CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_INVOER_DIALOG, pParent)
    , mApplication(app)
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

std::wstring InvoerDialog::GetPand() const
{
    return mApplication.GetPand();
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
    mInifile[GetPand()][L"lening"] = std::to_wstring(mLenen.GetValue());
}

void InvoerDialog::VulPandCombo()
{
    mPandCombo.Clear();
    for (auto pand : mApplication.GetPanden())
        mPandCombo.AddString(pand.c_str());
}

void InvoerDialog::VulDialoog()
{
    VulPandCombo();

    mPandCombo.SelectString(0, mApplication.GetPand().c_str());

    mKoopsomEdit.SetValue(Str::ToDouble(mInifile[GetPand()][L"koopsom"]));
    mTaxatieEdit.SetValue(Str::ToDouble(mInifile[L"invoer"][L"taxatie"]));
    mIngEdit.SetValue(Str::ToDouble(mInifile[L"invoer"][L"ingadvies"]));
    mRieksEdit.SetValue(Str::ToDouble(mInifile[L"invoer"][L"rieks"]));
    mNotarisEdit.SetValue(Str::ToDouble(mInifile[L"invoer"][L"notaris"]));
    mNhgEdit.SetValue(Str::ToDouble(mInifile[GetPand()][L"nhg"]));
    mKoopsomOverigen.SetValue(Str::ToDouble(mInifile[GetPand()][L"overige"]));
    mNatasjaEigenGeld.SetValue(Str::ToDouble(mInifile[L"invoer"][L"natasja"]));
}

void InvoerDialog::BewaarDialoog()
{
    mInifile[GetPand()][L"koopsom"] = std::to_wstring(mKoopsomEdit.GetValue());
    mInifile[GetPand()][L"nhg"] = std::to_wstring(mNhgEdit.GetValue());
    mInifile[GetPand()][L"overige"] = std::to_wstring(mKoopsomOverigen.GetValue());
}


void InvoerDialog::OnEnChangeKoopsomEdit()
{
    mInifile[GetPand()][L"koopsom"] = std::to_wstring(mKoopsomEdit.GetValue());
    HerberekenKoopsomTotaal();
}


void InvoerDialog::OnEnChangeTaxatieEdit()
{
    mInifile[L"invoer"][L"taxatie"] = std::to_wstring(mTaxatieEdit.GetValue());
    HerberekenKoopsomTotaal();
}


void InvoerDialog::OnEnChangeIngEdit()
{
    mInifile[L"invoer"][L"ingadvies"] = std::to_wstring(mIngEdit.GetValue());
    HerberekenKoopsomTotaal();
}


void InvoerDialog::OnEnChangeRieksEdit()
{
    mInifile[L"invoer"][L"rieks"] = std::to_wstring(mRieksEdit.GetValue());
}


void InvoerDialog::OnEnChangeNhgEdit()
{
    mInifile[GetPand()][L"nhg"] = std::to_wstring(mNhgEdit.GetValue());
    HerberekenKoopsomTotaal();
}


void InvoerDialog::OnEnChangeOverigEdit()
{
    mInifile[GetPand()][L"overige"] = std::to_wstring(mKoopsomOverigen.GetValue());
    HerberekenKoopsomTotaal();
}


void InvoerDialog::OnEnChangeKostenKoperTotaalEdit()
{
    HerberekenLening();
}


void InvoerDialog::OnEnChangeNatasjaEigenGeldEdit()
{
    mInifile[L"invoer"][L"natasja"] = std::to_wstring(mNatasjaEigenGeld.GetValue());
    HerberekenLening();
}


void InvoerDialog::OnEnChangeNotarisEdit()
{
    mInifile[L"invoer"][L"notaris"] = std::to_wstring(mNotarisEdit.GetValue());
    HerberekenKoopsomTotaal();
}


void InvoerDialog::OnBnClickedSaveButton()
{
    CString pand;
    mPandCombo.GetWindowText(pand);
    mApplication.SetPand((const wchar_t*)pand);
    VulDialoog();
}


void InvoerDialog::OnBnClickedDeleteButton()
{
    CString pand;
    mPandCombo.GetWindowText(pand);
    mApplication.DeletePand(pand.GetBuffer());
}
