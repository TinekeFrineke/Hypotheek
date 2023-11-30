#pragma once

#include "DoubleEdit.h"
#include "TabPage.h"

class Inifile;

// NatasjaLastenDialog dialog

class NatasjaLastenDialog
	: public CDialog
	, public TabPage
{
	DECLARE_DYNAMIC(NatasjaLastenDialog)

public:
	NatasjaLastenDialog(Inifile& inifile, CWnd* pParent = nullptr);   // standard constructor
	virtual ~NatasjaLastenDialog();

	virtual CDialog* GetDialog() override {
		return this;
	}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LASTEN_NATASJA_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	void BerekenTotaleLasten();

	Inifile& mInifile;

	CDoubleEdit mLening;
	CDoubleEdit mRentePercentage;
	CDoubleEdit mJaarrente;
	CDoubleEdit mSchenkingen;
	CDoubleEdit mRestJaarrente;
	CDoubleEdit mMaandrente;
	CDoubleEdit mVve;
	CDoubleEdit mErfpacht;
	CDoubleEdit mTotaleLasten;
public:
	afx_msg void OnEnChangeRentePercentageEdit();
	afx_msg void OnEnChangeSchenkingenEdit();
	afx_msg void OnEnChangeEditVve();
	afx_msg void OnEnChangeErfpachtEdit();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnEnChangeRestJaarrenteEdit();
private:
	CDoubleEdit mOpstalVerzekeringEdit;
public:
	afx_msg void OnEnChangeOpstalverzekeringEdit();
	afx_msg void OnEnChangeJaarrenteEdit();
};
