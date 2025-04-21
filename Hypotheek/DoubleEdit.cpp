#include "pch.h"

#include <assert.h>

#include "Utilities/StrUtils.h"

#include "DoubleEdit.h"
#include "StrConvert.h"


BEGIN_MESSAGE_MAP(CDoubleEdit, CEdit)
    //{{AFX_MSG_MAP(CDoubleEdit)
    ON_WM_CHAR()
    ON_WM_KILLFOCUS()
    //  ON_MESSAGE(WM_PASTE, OnPaste)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


bool CDoubleEdit::CheckContents()
{
    assert(m_hWnd != NULL);
    TCHAR text[1024];
    GetWindowText(text, 1023);

    return StrConvert::IsDouble(text);
}


double CDoubleEdit::GetValue() const
{
    assert(m_hWnd != NULL);
    TCHAR text[1024];
    GetWindowText(text, 1023);

    if (StrConvert::IsDouble(text))
        return StrConvert::ToDouble(text);
    else
        return 0;
}


void CDoubleEdit::SetValue(double aValue)
{
    assert(m_hWnd != NULL);
    TCHAR format[10];
    _stprintf_s(format, _T("%c.%df"), _T('%'), mDecimals);
    TCHAR buffer[1024];
    _stprintf_s(buffer, format, aValue);
    SetWindowText(buffer);
}


void CDoubleEdit::OnChar(UINT nChar, UINT nRepCount, UINT nFlags)
{
    if (!isdigit(nChar) && (nChar != '.' && nChar != ',' && nChar != _T('\b') && nChar != 0x16))
        return;

    CEdit::OnChar(nChar, nRepCount, nFlags);
}


void CDoubleEdit::OnKillFocus(CWnd* aWnd)
{
    if (!CheckContents())
        ::MessageBox(0, _T("Enter a double"), _T("Error"), MB_OK);

    CEdit::OnKillFocus(aWnd);
}
