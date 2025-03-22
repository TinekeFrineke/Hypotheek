// C:\Projects\VC2019\Hypotheek\Hypotheek\OverviewDialog.cpp : implementation file
//

#include "pch.h"
#include "C:\Projects\VC2019\Hypotheek\Hypotheek\OverviewDialog.h"
#include "afxdialogex.h"


// OverviewDialog dialog

IMPLEMENT_DYNAMIC(OverviewDialog, CDialogEx)

OverviewDialog::OverviewDialog(std::shared_ptr<IHypotheekOwner>& hypotheek, Inifile& inifile, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OVERVIEW_DIALOG, pParent)
	, m_hypotheek(hypotheek)
	, mInifile(inifile)
{

}

OverviewDialog::~OverviewDialog()
{
}

void OverviewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

CDialog* OverviewDialog::GetDialog()
{
	return this;
}


BEGIN_MESSAGE_MAP(OverviewDialog, CDialogEx)
END_MESSAGE_MAP()


// OverviewDialog message handlers
