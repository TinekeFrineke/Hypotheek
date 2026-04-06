// C:\Projects\VC2019\Hypotheek\Hypotheek\OverviewDialog.cpp : implementation file
//

#include "pch.h"

#include "OverviewDialog.h"

#include <algorithm>
#include <fstream>

#include "afxdialogex.h"

#include <HypotheekModel/HypotheekCalculation.h>
#include <HypotheekModel/HypotheekData.h>
#include <HypotheekModel/IHypotheek.h>
#include <HypotheekModel/OverzichtCreator.h>

#undef min
#undef max
// OverviewDialog dialog

IMPLEMENT_DYNAMIC(OverviewDialog, CDialogEx)

OverviewDialog::OverviewDialog(std::shared_ptr<IHypotheek> hypotheek, utils::Inifile& inifile, CWnd* pParent /*=nullptr*/)
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
    hypotheek::OverzichtCreator creator;
    m_hypotheek->accept(creator);

    const auto overzichtData(creator.collection());
    m_overviewData.clear();
    for (const auto & overzichtEntry : overzichtData)
        m_overviewData.push_back({ overzichtEntry.startDate, overzichtEntry.payment, overzichtEntry.interest,
                                overzichtEntry.repayment, overzichtEntry.remainingDebt });
    m_overviewList.View(m_overviewData);
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
    if (bShow)
        fillOverview();
}


void OverviewDialog::OnExportButtonClicked()
{
    if (m_type == Type::Yearly) {
        std::ofstream output("jaaroverzicht.csv");
        std::ofstream log("jaaroverzicht.log");

        output << "Datum,betaling,rente,aflossing,restschuld\n";
        std::map<int, OverviewData> yearlyData;
        for (const auto& entry : m_overviewData) {
            log << "processing " << entry.startDate
                << " payment " << entry.payment
                << " interest " << entry.interest
                << " repayment " << entry.repayment;
            auto& newEntry = yearlyData[entry.startDate.Year()];
            newEntry.payment += entry.payment;
            newEntry.interest += entry.interest;
            newEntry.repayment += entry.repayment;
            auto bedrag = std::min(newEntry.remainingDebt.ToDouble(), entry.remainingDebt.ToDouble());
            if (newEntry.remainingDebt == Finance::Bedrag(0.0))
                newEntry.remainingDebt = entry.remainingDebt;
            else
                newEntry.remainingDebt = Finance::Bedrag(std::min(newEntry.remainingDebt.ToDouble(), entry.remainingDebt.ToDouble()));
        }

        for (auto entry : yearlyData)
            output << entry.first << ','
            << entry.second.payment.ToString() << ','
            << entry.second.interest.ToString() << ','
            << entry.second.repayment.ToString() << ','
            << entry.second.remainingDebt.ToString() << '\n';

    }
    else {
        std::ofstream output("overzicht.csv");
        output << "Datum,betaling,rente,aflossing,restschuld\n";
        for (const auto& entry : m_overviewData)
            output << Utils::ToString(entry.startDate) << ','
            << entry.payment.ToString() << ','
            << entry.interest.ToString() << ','
            << entry.repayment.ToString() << ','
            << entry.remainingDebt.ToString() << '\n';
    }
}
