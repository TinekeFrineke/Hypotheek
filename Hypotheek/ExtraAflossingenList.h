#pragma once

#include <afxcmn.h>
#include <vector>

#include <Utilities/Bedrag.h>
#include <Utilities/date.h>

#include "ListControl.h"


struct ExtraAflossingData {
    Utils::Date date;
    Finance::Bedrag payment;
};

// Can contain both monthly and yearly data
class ExtraAflossingListItem
{
public:
    ExtraAflossingListItem(const ExtraAflossingData& anItem);

    void Write(CListCtrl& aControl, int iItemIndex);

    ExtraAflossingData GetItem() const;

private:
    ExtraAflossingData mItem;
};


class ExtraAflossingList
    : public ListControl
{
    // Construction
public:
    ExtraAflossingList();
    ~ExtraAflossingList() override;

    // Operations
    void View(const std::vector<ExtraAflossingData>& aItems);

    ExtraAflossingListItem* GetItemAt(int iIndex);
    ExtraAflossingListItem* GetSelectedItem();
    void RemoveSelectedItem();
    //void SelectItem(const weight::Item& anItem);
    //void SelectItem(int iIndex, bool bSelect);

protected:
    //DECLARE_MESSAGE_MAP()

    void ClearItems();

private:
    std::vector<ExtraAflossingListItem> mItems;
};

