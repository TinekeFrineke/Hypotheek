#pragma once

#include "afxcmn.h"

#include <string>


class CStringEdit : public CEdit
{
public:
  std::string GetValue() const;
  void SetValue(const std::string & aValue);
};
