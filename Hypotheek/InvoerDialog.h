#pragma once

#include "DoubleEdit.h"
#include "TabPage.h"

class Inifile;

// InvoerDialog dialog

class InvoerDialog
	: public CDialogEx
	, public TabPage
{
	DECLARE_DYNAMIC(InvoerDialog)

public:
	InvoerDialog(Inifile& inifile, CWnd* pParent = nullptr);   // standard constructor
	virtual ~InvoerDialog();

	virtual BOOL OnInitDialog() override;
	virtual CDialog* GetDialog() {
		return this;
	}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INVOER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	void HerberekenKoopsomTotaal();
	void HerberekenLening();

	Inifile& mInifile;

	CDoubleEdit mKoopsomEdit;
	CDoubleEdit mVerkoopMakelaarEdit;
	CDoubleEdit mTaxatieEdit;
	CDoubleEdit mIngEdit;
	CDoubleEdit mRieksEdit;
	CDoubleEdit mNhgEdit;
	CDoubleEdit mKoopsomOverigen;
	CDoubleEdit mKoopsomTotaal;
	CDoubleEdit mNatasjaEigenGeld;
	CDoubleEdit mLenen;
public:
	afx_msg void OnEnChangeKoopsomEdit();
	afx_msg void OnEnChangeVerkoopMakelaarEdit();
	afx_msg void OnEnChangeTaxatieEdit();
	afx_msg void OnEnChangeIngEdit();
	afx_msg void OnEnChangeRieksEdit();
	afx_msg void OnEnChangeNhgEdit();
	afx_msg void OnEnChangeOverigEdit();
	afx_msg void OnEnChangeKostenKoperTotaalEdit();
	afx_msg void OnEnChangeNatasjaEigenGeldEdit();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
