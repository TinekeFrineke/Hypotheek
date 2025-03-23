#pragma once

#include <memory>

#include "OverviewList.h"
#include "resource.h"
#include "TabPage.h"

class IHypotheek;
class Inifile;

// OverviewDialog dialog

class OverviewDialog
    : public CDialogEx
    , public TabPage
{
    DECLARE_DYNAMIC(OverviewDialog)

public:
    OverviewDialog(std::shared_ptr<IHypotheek> hypotheek, Inifile& inifile, CWnd* pParent = nullptr);
    ~OverviewDialog() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_OVERVIEW_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()

    virtual BOOL OnInitDialog() override;

    afx_msg void OnBnClickedRadioMonthly();
    afx_msg void OnBnClickedRadioYearly();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

private:
    enum class Type { Monthly, Yearly };

    // Inherited via TabPage
    virtual CDialog* GetDialog() override;

    void setMonthly();
    void setYearly();
    void fillOverview();
    void fillMonthlyOverview();
    void fillYearlyOverview();

    Type m_type{};
    std::shared_ptr<IHypotheek> m_hypotheek;
    Inifile& mInifile;

    OverviewList m_overviewList;
public:
    afx_msg void OnExportButtonClicked();
};
