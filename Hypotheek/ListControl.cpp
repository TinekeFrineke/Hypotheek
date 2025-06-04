
#include "ListControl.h"

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
