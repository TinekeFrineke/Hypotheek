#pragma once

#include "afxcmn.h"

#include "Utilities/StrUtils.h"


class CStringEdit : public CEdit
{
public:
  std::tstring        GetValue() const;
  void                SetValue(const std::tstring & aValue);

protected:
};
