// ExtraAflossingenDialog.cpp : implementation file
//

#include "pch.h"
#include "ExtraAflossingenDialog.h"
#include "afxdialogex.h"


// ExtraAflossingenDialog dialog

IMPLEMENT_DYNAMIC(ExtraAflossingenDialog, CDialogEx)

ExtraAflossingenDialog::ExtraAflossingenDialog(std::shared_ptr<IHypotheekOwner> hypotheek, Inifile& inifile, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXTRA_AFLOSSINGEN, pParent)
    , mInifile(inifile)
    , m_hypotheek(std::move(hypotheek))
{

}

ExtraAflossingenDialog::~ExtraAflossingenDialog()
{
}

void ExtraAflossingenDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ExtraAflossingenDialog, CDialogEx)
END_MESSAGE_MAP()


// ExtraAflossingenDialog message handlers
