// NatasjaLastenDialog.cpp : implementation file
//

#include "pch.h"
#include "Hypotheek.h"
#include "NatasjaLastenDialog.h"
#include <Utilities/Inifile.h>
#include <Utilities/strutils.h>

#include "afxdialogex.h"
#include "Hypotheek.h"


// NatasjaLastenDialog dialog

IMPLEMENT_DYNAMIC(NatasjaLastenDialog, CDialog)

NatasjaLastenDialog::NatasjaLastenDialog(Inifile& inifile, CWnd* pParent /*=nullptr*/)
    : CDialog(IDD_LASTEN_NATASJA_DIALOG, pParent)
    , mInifile(inifile)
{

}

NatasjaLastenDialog::~NatasjaLastenDialog()
{
}


void NatasjaLastenDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
    __super::OnShowWindow(bShow, nStatus);

    mLening.SetValue(Str::ToDouble(mInifile[L"natasja"][L"lening"]));
    mRentePercentage.SetValue(Str::ToDouble(mInifile[L"natasja"][L"rentepercentage"]));
    mSchenkingen.SetValue(Str::ToDouble(mInifile[L"natasja"][L"schenkingen"]));
    mVve.SetValue(Str::ToDouble(mInifile[L"natasja"][L"vve"]));
    mErfpacht.SetValue(Str::ToDouble(mInifile[L"natasja"][L"erfpacht"]));
    mOpstalVerzekeringEdit.SetValue(Str::ToDouble(mInifile[L"natasja"][L"opstal"]));
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
END_MESSAGE_MAP()


// NatasjaLastenDialog message handlers


void NatasjaLastenDialog::OnEnChangeRentePercentageEdit()
{
    mInifile[L"natasja"][L"rentepercentage"] = std::to_wstring(mRentePercentage.GetValue());
    mJaarrente.SetValue(mLening.GetValue() * mRentePercentage.GetValue() / 100.0);
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
    mInifile[L"natasja"][L"vve"] = std::to_wstring(mVve.GetValue());
    BerekenTotaleLasten();
}


void NatasjaLastenDialog::OnEnChangeErfpachtEdit()
{
    mInifile[L"natasja"][L"erfpacht"] = std::to_wstring(mErfpacht.GetValue());
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
