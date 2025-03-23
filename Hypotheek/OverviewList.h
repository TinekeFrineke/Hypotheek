#pragma once

#include <afxcmn.h>
#include <vector>

#include <Utilities/Bedrag.h>
#include <Utilities/date.h>


class ListControl: public CListCtrl
{
public:
    ~ListControl() override = default;

    void SetNumberOfColumns(int aColumns);

    struct ColInfo
    {
        ColInfo() : mHeader(_T("")) {}
        ColInfo(int aMinWidth, int anAlignment, const TCHAR* aHeader)
            : mMinWidth(aMinWidth), mAlignment(anAlignment), mHeader(aHeader) {}
        int mMinWidth{ };
        int mAlignment{ LVCFMT_LEFT };
        const TCHAR* mHeader;
    };

    void SetColumnInfo(int iColumn, const ColInfo& aInfo);

    // Operations
    void Initialize();

private:
    std::vector<ColInfo> mColumnInfo;
    int mNumberOfColumns{};
};


struct OverviewData {
    Utils::Date startDate;
    Finance::Bedrag payment;
    Finance::Bedrag interest;
    Finance::Bedrag repayment;
    Finance::Bedrag remainingDebt;
};

// Can contain both monthly and yearly data
class OverviewListItem
{
public:
    OverviewListItem(OverviewData anItem);

    void Write(CListCtrl& aControl, int iItemIndex);

    OverviewData GetItem();

private:
    OverviewData mItem;
};


class OverviewList:
    public ListControl
{
    // Construction
public:
    OverviewList();
    ~OverviewList() override;

    // Operations
    void View(const std::vector<OverviewData>& aItems);

    //OverviewListItem* GetItemAt(int iIndex);
    //OverviewListItem* GetSelectedItem();
    //void SelectItem(const weight::Item& anItem);
    //void SelectItem(int iIndex, bool bSelect);

protected:
    //DECLARE_MESSAGE_MAP()

    void ClearItems();

private:
    std::vector<OverviewListItem> mItems;
};

