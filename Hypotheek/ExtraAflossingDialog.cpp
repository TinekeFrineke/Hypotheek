// ExtraAflossingDialog.cpp : implementation file
//

#include "pch.h"

#include "ExtraAflossingDialog.h"
#include "afxdialogex.h"

#include "utilities/Date.h"
#include "utilities/StrUtils.h"

// ExtraAflossingDialog dialog

IMPLEMENT_DYNAMIC(ExtraAflossingDialog, CDialogEx)

ExtraAflossingDialog::ExtraAflossingDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NIEUWE_EXTRA_AFLOSSING, pParent)
{

}

ExtraAflossingDialog::~ExtraAflossingDialog()
{
}

void ExtraAflossingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATUM, m_editDate);
	DDX_Control(pDX, IDC_BEDRAG, m_editBedrag);
}


BEGIN_MESSAGE_MAP(ExtraAflossingDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &ExtraAflossingDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// ExtraAflossingDialog message handlers


BOOL ExtraAflossingDialog::OnInitDialog()
{
	if (!CDialogEx::OnInitDialog())
		return false;

	m_editDate.SetWindowText(Str::ToWString(ToString(Utils::Today())).c_str());
	return 0;
}

void ExtraAflossingDialog::OnBnClickedOk()
{
	CString text;
	m_editDate.GetWindowText(text);
	try {
		m_date = Utils::ToDate(Str::ToString(static_cast<const wchar_t*>(text)));
		m_bedrag = Finance::Bedrag(m_editBedrag.GetValue());
	}
	catch (...) {
		::MessageBox(m_hWnd, (const wchar_t*)(CString(L"Wrong date: ") + text), L"ERROR", MB_OK);
		return;
	}

	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
