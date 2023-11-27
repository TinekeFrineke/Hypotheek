#include "pch.h"

#include "StringEdit.h"

#include <assert.h>

std::tstring CStringEdit::GetValue() const
{
  assert(m_hWnd != NULL);
  CString text;
  GetWindowText(text);
  return (const TCHAR *)text;
}


void CStringEdit::SetValue(const std::tstring & aValue)
{
  assert(m_hWnd != NULL);
  SetWindowText(aValue.c_str());
}

