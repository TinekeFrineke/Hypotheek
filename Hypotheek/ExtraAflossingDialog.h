#pragma once


// ExtraAflossingDialog dialog
#include <utilities/Bedrag.h>
#include <utilities/Date.h>

#include "DoubleEdit.h"
#include "resource.h"


class ExtraAflossingDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ExtraAflossingDialog)

public:
	ExtraAflossingDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ExtraAflossingDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NIEUWE_EXTRA_AFLOSSING };
#endif

	BOOL OnInitDialog() override;
	afx_msg void OnBnClickedOk();

	Utils::Date GetDate() const { return m_date; }
	Finance::Bedrag GetBedrag() const { return m_bedrag; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editDate;
	CDoubleEdit m_editBedrag;

	Utils::Date m_date;
	Finance::Bedrag m_bedrag;
};
