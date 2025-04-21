#include "OverviewList.h"

#include "StrConvert.h"

void ListControl::SetNumberOfColumns(int aColumns)
{
    mNumberOfColumns = aColumns;
    mColumnInfo.resize(aColumns);
}

void ListControl::SetColumnInfo(int iColumn, const ColInfo& aInfo)
{
    if (iColumn >= mNumberOfColumns)
        throw 0;

    mColumnInfo[iColumn] = aInfo;
}

void ListControl::Initialize()
{
    for (int i = 0; i < mNumberOfColumns; ++i)
        InsertColumn(i + 1, mColumnInfo[i].mHeader, mColumnInfo[i].mAlignment, mColumnInfo[i].mMinWidth);
}

OverviewListItem::OverviewListItem(OverviewData anItem)
    : mItem(anItem) {}

void OverviewListItem::Write(CListCtrl& aControl, int iItemIndex)
{
    LV_ITEM lvi;
    memset(&lvi, 0, sizeof(LV_ITEM));

    lvi.mask = LVIF_TEXT | LVIF_PARAM/* | LVIF_IMAGE | LVIF_STATE*/;
    lvi.iItem = iItemIndex;

    // Start date
    lvi.iSubItem = 0;
    lvi.pszText = _tcsdup(StrConvert::Utf8ToUtf16(ToString(mItem.startDate)).c_str());
    lvi.lParam = (LPARAM)&mItem;

    int index = aControl.InsertItem(&lvi);

    aControl.SetItemText(index, 0, StrConvert::Utf8ToUtf16(ToString(mItem.startDate)).c_str());
    aControl.SetItemText(index, 1, StrConvert::Utf8ToUtf16(mItem.payment.ToString()).c_str());
    aControl.SetItemText(index, 2, StrConvert::Utf8ToUtf16(mItem.interest.ToString()).c_str());
    aControl.SetItemText(index, 3, StrConvert::Utf8ToUtf16(mItem.repayment.ToString()).c_str());
    aControl.SetItemText(index, 4, StrConvert::Utf8ToUtf16(mItem.remainingDebt.ToString()).c_str());
    aControl.SetItemData(index, (DWORD_PTR)this);
}

OverviewData OverviewListItem::GetItem()
{
    return mItem;
}

OverviewList::OverviewList()
{
    SetNumberOfColumns(5);
    SetColumnInfo(0, ColInfo(100, LVCFMT_LEFT, _T("Datum")));
    SetColumnInfo(1, ColInfo(50, LVCFMT_RIGHT, _T("Betaling")));
    SetColumnInfo(2, ColInfo(50, LVCFMT_RIGHT, _T("Rente")));
    SetColumnInfo(3, ColInfo(50, LVCFMT_RIGHT, _T("Aflossing")));
    SetColumnInfo(4, ColInfo(70, LVCFMT_RIGHT, _T("Restschuld")));
}

OverviewList::~OverviewList()
{
}

void OverviewList::View(const std::vector<OverviewData>& aItems)
{
    SetRedraw(FALSE);
    DeleteAllItems();
    ClearItems();

    SetItemCount((int)aItems.size());
    for (size_t i = 0; i < aItems.size(); ++i)
        mItems.push_back(OverviewListItem(aItems[i]));

    for (size_t i = 0; i < mItems.size(); ++i)
        mItems[i].Write(*this, (int)i);

    if (mItems.size() > 0)
    {
        LVITEM item;
        item.iItem = 0;
        item.mask = LVIF_STATE;
        //SelectItem(0, true);
    }

    for (int i = 0; i < 2; ++i)
        SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
    SetRedraw(TRUE);
}

void OverviewList::ClearItems()
{
}
