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
	ON_BN_CLICKED(IDC_BUTTON1, &ExtraAflossingenDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ExtraAflossingenDialog::OnBnClickedButton2)
END_MESSAGE_MAP()


// ExtraAflossingenDialog message handlers


BOOL ExtraAflossingenDialog::OnInitDialog()
{
	if (!CDialogEx::OnInitDialog())
		return false;

	m_aflossingenList.Initialize();
	m_aflossingenList.SetSelectionMark(0);
	m_aflossingenList.ShowWindow(SW_SHOW);
	return true;
}


void ExtraAflossingenDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	View();
}


void ExtraAflossingenDialog::OnBnClickedButton1()
{
	ExtraAflossingDialog dialog(this);
	if (dialog.DoModal() == IDOK) {
		m_hypotheek->setExtraAflossing(dialog.GetDate(), dialog.GetBedrag());
		View();
	}
}


void ExtraAflossingenDialog::OnBnClickedButton2()
{
	const auto item = m_aflossingenList.GetSelectedItem();
	if (item == nullptr)
		return;

	m_hypotheek->removeExtraAflossing(item->GetItem().date);
	mInifile.erase("ExtraAflossingen", ToString(item->GetItem().date));
	m_aflossingenList.RemoveSelectedItem();
}


void ExtraAflossingenDialog::View()
{
	const auto alist{ m_hypotheek->getExtraAflossings() };
	std::vector<ExtraAflossingData> extras;
	for (const auto& aflossing : alist)
		extras.push_back({ aflossing.first, aflossing.second });
	m_aflossingenList.View(extras);
}
