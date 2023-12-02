
// Hypotheek.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include <string>
#include <vector>
#include "resource.h"		// main symbols

#include <Utilities/Inifile.h>


// HypotheekApplication:
// See Hypotheek.cpp for the implementation of this class
//

class HypotheekApplication : public CWinApp
{
public:
	HypotheekApplication();

// Overrides
public:
	virtual BOOL InitInstance();

	std::wstring GetPand() const;
	std::vector<std::wstring> GetPanden() const;
	void SetPand(const std::wstring& pand);
	void DeletePand(const std::wstring& pand);

	// Implementation

	DECLARE_MESSAGE_MAP()

private:
	std::wstring GetCurrentDir() const;
	void VulPandenUitInifile();
	void PandenToInifile();

	Inifile mInifile;
	std::vector<std::wstring> mPanden;
	std::wstring mPand;
};

extern HypotheekApplication theApp;
