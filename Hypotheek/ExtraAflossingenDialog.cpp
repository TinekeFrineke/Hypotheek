// ExtraAflossingenDialog.cpp : implementation file
//

#include "pch.h"
#include "ExtraAflossingenDialog.h"
#include "afxdialogex.h"

#include <utilities/Inifile.h>

#include "ExtraAflossingDialog.h"
#include "IHypotheekOwner.h"


// ExtraAflossingenDialog dialog

IMPLEMENT_DYNAMIC(ExtraAflossingenDialog, CDialogEx)

ExtraAflossingenDialog::ExtraAflossingenDialog(std::shared_ptr<IHypotheekOwner> hypotheek, utils::Inifile& inifile, CWnd* pParent /*=nullptr*/)
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
	DDX_Control(pDX, IDC_AFLOSSINGEN_LIST, m_aflossingenList);
}

BEGIN_MESSAGE_MAP(ExtraAflossingenDialog, CDialogEx)
	ON_BN_CLICKED(IDC_OK, &ExtraAflossingenDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CANCEL, &ExtraAflossingenDialog::OnBnClickedCancel)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// ExtraAflossingenDialog message handlers


BOOL ExtraAflossingenDialog::OnInitDialog()
{
	if (!CDialogEx::OnInitDialog())
		return false;

	m_aflossingenList.Initialize();
	m_aflossingenList.SetSelectionMark(0);
	View();
	m_aflossingenList.ShowWindow(SW_SHOW);
	View();
	return true;
}


void ExtraAflossingenDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);
	View();
}


void ExtraAflossingenDialog::View()
{
	const auto alist{ m_hypotheek->getExtraAflossings() };
	std::vector<ExtraAflossingData> extras;
	for (const auto& aflossing : alist)
		extras.push_back({ aflossing.first, aflossing.second });
	m_aflossingenList.View(extras);
}


void ExtraAflossingenDialog::OnBnClickedOk()
{
	ExtraAflossingDialog dialog(this);
	if (dialog.DoModal() == IDOK) {
		m_hypotheek->setExtraAflossing(dialog.GetDate(), dialog.GetBedrag());
		View();
	}
}


void ExtraAflossingenDialog::OnBnClickedCancel()
{
	const auto item = m_aflossingenList.GetSelectedItem();
	if (item == nullptr)
		return;

	m_hypotheek->removeExtraAflossing(item->GetItem().date);
	mInifile.erase("ExtraAflossingen", ToString(item->GetItem().date));
	m_aflossingenList.RemoveSelectedItem();
}
