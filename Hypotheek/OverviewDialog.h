#pragma once

#include <memory>

#include "resource.h"
#include "TabPage.h"

class IHypotheekOwner;
class Inifile;

// OverviewDialog dialog

class OverviewDialog
    : public CDialogEx
    , public TabPage
{
    DECLARE_DYNAMIC(OverviewDialog)

public:
    OverviewDialog(std::shared_ptr<IHypotheekOwner>& hypotheek, Inifile& inifile, CWnd* pParent = nullptr);   // standard constructor
    virtual ~OverviewDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_OVERVIEW_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()

private:
    // Inherited via TabPage
    virtual CDialog* GetDialog() override;

    std::shared_ptr<IHypotheekOwner>& m_hypotheek;
    Inifile& mInifile;
};
