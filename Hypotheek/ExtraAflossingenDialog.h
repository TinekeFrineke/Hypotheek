#pragma once


// ExtraAflossingenDialog dialog
#include <afxdialogex.h>

#include <memory>

#include "ExtraAflossingenList.h"
#include "resource.h"
#include "TabPage.h"

class Inifile;
class IHypotheekOwner;


class ExtraAflossingenDialog
	: public CDialogEx
    , public TabPage
{
	DECLARE_DYNAMIC(ExtraAflossingenDialog)

public:
	ExtraAflossingenDialog(std::shared_ptr<IHypotheekOwner> hypotheek, Inifile& inifile, CWnd* pParent = nullptr);
    ~ExtraAflossingenDialog() override;

    virtual CDialog* GetDialog() override {
        return this;
    }
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXTRA_AFLOSSINGEN };
#endif

    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();

    BOOL OnInitDialog() override;
    void OnShowWindow(BOOL bShow, UINT nStatus);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
    
private:
    void View();

    Inifile& mInifile;
    std::shared_ptr<IHypotheekOwner> m_hypotheek;
    ExtraAflossingList m_aflossingenList;
};
