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
