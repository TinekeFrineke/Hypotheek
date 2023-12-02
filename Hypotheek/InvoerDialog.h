#pragma once

#include <string>

#include "DoubleEdit.h"
#include "TabPage.h"

class HypotheekApplication;
class Inifile;

// InvoerDialog dialog

class InvoerDialog
	: public CDialogEx
	, public TabPage
{
	DECLARE_DYNAMIC(InvoerDialog)

public:
	InvoerDialog(HypotheekApplication& application, Inifile& inifile, CWnd* pParent = nullptr);   // standard constructor
	virtual ~InvoerDialog();

	virtual BOOL OnInitDialog() override;
	virtual CDialog* GetDialog() {
		return this;
	}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INVOER_DIALOG };
#endif

public:
	afx_msg void OnEnChangeKoopsomEdit();
	afx_msg void OnEnChangeTaxatieEdit();
	afx_msg void OnEnChangeIngEdit();
	afx_msg void OnEnChangeRieksEdit();
	afx_msg void OnEnChangeNhgEdit();
	afx_msg void OnEnChangeOverigEdit();
	afx_msg void OnEnChangeKostenKoperTotaalEdit();
	afx_msg void OnEnChangeNatasjaEigenGeldEdit();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnEnChangeNotarisEdit();
	afx_msg void OnBnClickedSaveButton();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	std::wstring GetPand() const;
	void HerberekenKoopsomTotaal();
	void HerberekenLening();
	void VulPandCombo();
	void VulDialoog();
	void BewaarDialoog();

	Inifile& mInifile;

	CDoubleEdit mKoopsomEdit;
	CDoubleEdit mTaxatieEdit;
	CDoubleEdit mIngEdit;
	CDoubleEdit mRieksEdit;
	CDoubleEdit mNhgEdit;
	CDoubleEdit mKoopsomOverigen;
	CDoubleEdit mKoopsomTotaal;
	CDoubleEdit mNatasjaEigenGeld;
	CDoubleEdit mLenen;
	CDoubleEdit mNotarisEdit;

	HypotheekApplication& mApplication;
	CComboBox mPandCombo;
public:
	afx_msg void OnBnClickedDeleteButton();
};
