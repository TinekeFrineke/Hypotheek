#include "pch.h"

#include "StringEdit.h"

#include <assert.h>

#include "StrConvert.h"

std::string CStringEdit::GetValue() const
{
  assert(m_hWnd != NULL);
  CString text;
  GetWindowText(text);
  return StrConvert::Utf16ToUtf8((const wchar_t *)text);
}


void CStringEdit::SetValue(const std::string & aValue)
{
  assert(m_hWnd != NULL);
  SetWindowText(StrConvert::Utf8ToUtf16(aValue).c_str());
}

