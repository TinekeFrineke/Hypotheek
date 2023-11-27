#pragma once

#include "afxcmn.h"


class CDoubleEdit
    : public CEdit
{
public:
                      CDoubleEdit() : mDecimals(2) {}

  void                SetDecimals(int aDecimals) { mDecimals = aDecimals; }
  double              GetValue() const;
  void                SetValue(double aValue);

protected:
	//{{AFX_MSG(CDoubleEdit)
  afx_msg void OnKillFocus( CWnd* );
  afx_msg void OnChar( UINT, UINT, UINT );
//  afx_msg LRESULT         OnPaste(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

 	DECLARE_MESSAGE_MAP()

  bool                CheckContents();

private:
  int                 mDecimals;
};
