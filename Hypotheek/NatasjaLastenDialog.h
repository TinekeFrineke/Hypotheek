#pragma once

#include "DoubleEdit.h"
#include "resource.h"
#include "TabPage.h"

class Inifile;
class IHypotheekOwner;

// NatasjaLastenDialog dialog

class NatasjaLastenDialog
	: public CDialog
	, public TabPage
{
	DECLARE_DYNAMIC(NatasjaLastenDialog)

public:
	NatasjaLastenDialog(std::shared_ptr<IHypotheekOwner> hypotheek, Inifile& inifile, CWnd* pParent = nullptr);   // standard constructor
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
	afx_msg void OnEnChangeOpstalverzekeringEdit();
	afx_msg void OnEnChangeJaarrenteEdit();
	afx_msg void OnBnClickedRadioAnnuitair();
	afx_msg void OnBnClickedRadioAflossingsvrij();
	afx_msg void OnEnKillfocusEditStartdatum();

private:
	CDoubleEdit mOpstalVerzekeringEdit;
	CButton mRadioAnnuitair;
	CButton mRadioAflossingsvrij;
	CEdit mStartDatum;

	//HypotheekApplication& mApplication;
	Inifile& mInifile;
	std::shared_ptr<IHypotheekOwner> m_hypotheek;
};
