
// CHypotheekDialog.h : header file
//

#pragma once

#include <memory>

#include "MyTabControl.h"

class HypotheekOwner;
namespace utils {
class Inifile;
}

// CHypotheekDialog dialog
class CHypotheekDialog : public CDialogEx
{
// Construction
public:
	CHypotheekDialog(HypotheekApplication& application, utils::Inifile& inifile, CWnd* pParent = nullptr);
	~CHypotheekDialog() override;

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
	afx_msg void OnDestroy();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	std::shared_ptr<HypotheekOwner> m_hypotheekOwner;

	HypotheekApplication& mApplication;
	MyTabControl mTabControl;
	utils::Inifile& mInifile;
};
