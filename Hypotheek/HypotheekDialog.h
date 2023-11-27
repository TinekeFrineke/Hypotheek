
// CHypotheekDialog.h : header file
//

#pragma once

#include "MyTabControl.h"

class Inifile;

// CHypotheekDialog dialog
class CHypotheekDialog : public CDialogEx
{
// Construction
public:
	CHypotheekDialog(Inifile& inifile, CWnd* pParent = nullptr);	// standard constructor
	~CHypotheekDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HYPOTHEEK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	MyTabControl mTabControl;
	Inifile& mInifile;
};
