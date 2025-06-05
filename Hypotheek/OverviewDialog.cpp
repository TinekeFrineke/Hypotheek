// C:\Projects\VC2019\Hypotheek\Hypotheek\OverviewDialog.cpp : implementation file
//

#include "pch.h"

#include "OverviewDialog.h"

#include <fstream>

#include "afxdialogex.h"

#include <HypotheekModel/HypotheekCalculation.h>
#include <HypotheekModel/HypotheekData.h>
#include <HypotheekModel/IHypotheek.h>
#include <HypotheekModel/OverzichtCreator.h>

// OverviewDialog dialog

IMPLEMENT_DYNAMIC(OverviewDialog, CDialogEx)

OverviewDialog::OverviewDialog(std::shared_ptr<IHypotheek> hypotheek, Inifile& inifile, CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OVERVIEW_DIALOG, pParent)
    , m_hypotheek(std::move(hypotheek))
    , mInifile(inifile)
{
}

OverviewDialog::~OverviewDialog()
{
}

void OverviewDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_OVERVIEW_LIST, m_overviewList);
}

BOOL OverviewDialog::OnInitDialog()
{
    if (!CDialogEx::OnInitDialog())
        return false;

    CheckDlgButton(IDC_RADIO_MONTHLY, 1);
    m_overviewList.Initialize();
    m_overviewList.SetSelectionMark(0);
    m_overviewList.ShowWindow(SW_SHOW);

    return true;
}

CDialog* OverviewDialog::GetDialog()
{
    return this;
}

void OverviewDialog::setMonthly()
{
    m_type = Type::Monthly;
}

void OverviewDialog::setYearly()
{
    m_type = Type::Yearly;
}

void OverviewDialog::fillOverview()
{
    if (m_type == Type::Monthly) {
        fillMonthlyOverview();
    }
    else {
        fillYearlyOverview();
    }
}

void OverviewDialog::fillMonthlyOverview()
{
    const auto metrics = hypotheek::CreateMonthMetrics(*m_hypotheek);
    std::vector<OverviewData> overviewData;
    for (const auto& metric : metrics) {
        OverviewData data;
        data.startDate = metric.startDate;
        data.payment = metric.payment;
        data.interest = metric.interest;
        data.repayment = metric.repayment;
        data.remainingDebt = metric.remainingDebt;
        overviewData.push_back(data);
    }

    m_overviewList.View(overviewData);
}

void OverviewDialog::fillYearlyOverview()
{
}


BEGIN_MESSAGE_MAP(OverviewDialog, CDialogEx)
    ON_BN_CLICKED(IDC_RADIO_MONTHLY, &OverviewDialog::OnBnClickedRadioMonthly)
    ON_BN_CLICKED(IDC_RADIO_YEARLY, &OverviewDialog::OnBnClickedRadioYearly)
    ON_WM_SHOWWINDOW()
    ON_BN_CLICKED(ID_WINDOW_TILE_VERT, &OverviewDialog::OnExportButtonClicked)
END_MESSAGE_MAP()


// OverviewDialog message handlers


void OverviewDialog::OnBnClickedRadioMonthly()
{
    setMonthly();
}


void OverviewDialog::OnBnClickedRadioYearly()
{
    setYearly();
}


void OverviewDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
    fillOverview();

    m_hypotheek->setExtraAflossing(Utils::Today(), Finance::Bedrag(10000.0));

    hypotheek::OverzichtCreator creator;
    m_hypotheek->accept(creator);
    //std::cout << "Hypotheek == 0x" << reinterpret_cast<int>()
}


void OverviewDialog::OnExportButtonClicked()
{
    const auto metrics = hypotheek::CreateMonthMetrics(*m_hypotheek);
    std::ofstream output(u8"overzicht.csv");
    output << "Datum,betaling,rente,aflossing,restschuld\n";
    for (const auto& metric : metrics)
        output << ToString(metric.startDate) << L','
               << metric.payment.ToString() << L','
               << metric.interest.ToString() << L','
               << metric.repayment.ToString() << L','
               << metric.remainingDebt.ToString() << L'\n';
}
