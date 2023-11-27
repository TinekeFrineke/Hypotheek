#pragma once

#include "pch.h"
#include "afxcmn.h"

#include <vector>


class TabPage;

/////////////////////////////////////////////////////////////////////////////
// CMyTabControl window

class MyTabControl : public CTabCtrl
{
// Construction
public:
	          MyTabControl();
	virtual   ~MyTabControl();

	void      AddPage(TabPage * aPage, UINT aResourceID, TCHAR * aName);

	void      Initialize();
	void      SelectPage(int iPage);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTabControl)
	//}}AFX_VIRTUAL

// Implementation
	// Generated message map functions

protected:
	//{{AFX_MSG(CMyTabControl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
  struct DialogData
  {
                          DialogData(TabPage * aDialog, UINT anID, TCHAR * aName)
                            : mDialog(aDialog), mResourceID(anID), mName(aName) {}
    TabPage *             mDialog;
    UINT                  mResourceID;
    TCHAR *               mName;
  };

	void                    SetRectangle();
  void                    UpdateSelection();

  std::vector<DialogData> m_tabPages;
	int                     m_tabCurrent;
	int                     m_nNumberOfPages;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
