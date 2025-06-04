#include "ExtraAflossingenList.h"

#include "StrConvert.h"

ExtraAflossingListItem::ExtraAflossingListItem(const ExtraAflossingData& anItem)
    : mItem(anItem)
{
}

void ExtraAflossingListItem::Write(CListCtrl& aControl, int iItemIndex)
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

ExtraAflossingData ExtraAflossingListItem::GetItem() const
{
    return mItem;
}

ExtraAflossingList::ExtraAflossingList()
{
    SetNumberOfColumns(5);
    SetColumnInfo(0, ColInfo(100, LVCFMT_LEFT, _T("Datum")));
    SetColumnInfo(1, ColInfo(50, LVCFMT_RIGHT, _T("Betaling")));
    SetColumnInfo(2, ColInfo(50, LVCFMT_RIGHT, _T("Rente")));
    SetColumnInfo(3, ColInfo(50, LVCFMT_RIGHT, _T("Aflossing")));
    SetColumnInfo(4, ColInfo(70, LVCFMT_RIGHT, _T("Restschuld")));
}

ExtraAflossingList::~ExtraAflossingList()
{
}

void ExtraAflossingList::View(const std::vector<ExtraAflossingData>& aItems)
{
    SetRedraw(FALSE);
    DeleteAllItems();
    ClearItems();

    SetItemCount((int)aItems.size());
    for (size_t i = 0; i < aItems.size(); ++i)
        mItems.push_back(ExtraAflossingListItem(aItems[i]));

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

void ExtraAflossingList::ClearItems()
{
}
