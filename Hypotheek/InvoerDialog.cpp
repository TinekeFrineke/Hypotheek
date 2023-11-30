// InvoerDialog.cpp : implementation file
//

#include "pch.h"

#include "InvoerDialog.h"

#include "Hypotheek.h"
#include "afxdialogex.h"

#include <Utilities/Inifile.h>


// InvoerDialog dialog

IMPLEMENT_DYNAMIC(InvoerDialog, CDialogEx)

InvoerDialog::InvoerDialog(Inifile& inifile, CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_INVOER_DIALOG, pParent)
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

    mKoopsomEdit.SetValue(Str::ToDouble(mInifile[L"invoer"][L"koopsom"]));
    mTaxatieEdit.SetValue(Str::ToDouble(mInifile[L"invoer"][L"taxatie"]));
    mIngEdit.SetValue(Str::ToDouble(mInifile[L"invoer"][L"ingadvies"]));
    mRieksEdit.SetValue(Str::ToDouble(mInifile[L"invoer"][L"rieks"]));
    mNhgEdit.SetValue(Str::ToDouble(mInifile[L"invoer"][L"nhg"]));
    mKoopsomOverigen.SetValue(Str::ToDouble(mInifile[L"invoer"][L"overige"]));
    mNatasjaEigenGeld.SetValue(Str::ToDouble(mInifile[L"invoer"][L"natasja"]));
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
END_MESSAGE_MAP()


// InvoerDialog message handlers

void InvoerDialog::HerberekenKoopsomTotaal()
{
    mKoopsomTotaal.SetValue(mKoopsomEdit.GetValue()
                            + mTaxatieEdit.GetValue()
                            + mRieksEdit.GetValue()
                            + mNhgEdit.GetValue()
                            + mKoopsomOverigen.GetValue());
}

void InvoerDialog::HerberekenLening()
{
    mLenen.SetValue(mKoopsomTotaal.GetValue() - mNatasjaEigenGeld.GetValue());
    mInifile[L"natasja"][L"lening"] = std::to_wstring(mLenen.GetValue());
}


void InvoerDialog::OnEnChangeKoopsomEdit()
{
    mInifile[L"invoer"][L"koopsom"] = std::to_wstring(mKoopsomEdit.GetValue());
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
    HerberekenKoopsomTotaal();
}


void InvoerDialog::OnEnChangeNhgEdit()
{
    mInifile[L"invoer"][L"nhg"] = std::to_wstring(mNhgEdit.GetValue());
    HerberekenKoopsomTotaal();
}


void InvoerDialog::OnEnChangeOverigEdit()
{
    mInifile[L"invoer"][L"overige"] = std::to_wstring(mKoopsomOverigen.GetValue());
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
