
// Hypotheek.cpp : Defines the class behaviors for the application.
//

#include "pch.h"

#include <Utilities/Inifile.h>
#include <Utilities/strutils.h>

#include "framework.h"
#include "Hypotheek.h"
#include "HypotheekDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// HypotheekApplication

BEGIN_MESSAGE_MAP(HypotheekApplication, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


namespace {
const std::wstring unspecifiedPand(L"<unspecified>");
}

// HypotheekApplication construction

HypotheekApplication::HypotheekApplication()
	: mInifile(GetCurrentDir() + _T("\\hypotheek.ini"))
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only HypotheekApplication object

HypotheekApplication theApp;


// HypotheekApplication initialization

BOOL HypotheekApplication::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	VulPandenUitInifile();

	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	CHypotheekDialog dlg(*this, mInifile);
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	mInifile.Write();

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

std::wstring HypotheekApplication::GetPand() const
{
	return mPand;
}

std::vector<std::wstring> HypotheekApplication::GetPanden() const
{
	return mPanden;
}

void HypotheekApplication::SetPand(const std::wstring& pand)
{
	mPand = pand;
	auto pandIter(std::find(mPanden.begin(), mPanden.end(), pand));
	if (pandIter == mPanden.end())
		mPanden.emplace_back(pand);

	PandenToInifile();
}

void HypotheekApplication::DeletePand(const std::wstring& pand)
{
	if (pand == unspecifiedPand)
		return;

	auto pandIter(std::find(mPanden.begin(), mPanden.end(), pand));
	if (pandIter != mPanden.end()) {
		if (pand == mPand)
			if (pandIter != mPanden.begin())
				mPand = *(pandIter - 1);
			else if (pandIter != mPanden.end() - 1)
				mPand = *(pandIter + 1);
			else
				mPand = unspecifiedPand;
		mPanden.erase(pandIter);
	}

	PandenToInifile();
}

std::wstring HypotheekApplication::GetCurrentDir() const
{
	TCHAR dir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, dir);
	return dir;
}

void HypotheekApplication::VulPandenUitInifile()
{
	mPand = mInifile[L"panden"][L"huidigpand"];
	if (mPand.empty())
		mPand = unspecifiedPand;

	for (auto pand : mInifile[L"panden"])
		mPanden.push_back(pand.second);

	auto pandIter(std::find(mPanden.begin(), mPanden.end(), unspecifiedPand));
	if (pandIter == mPanden.end())
		mPanden.insert(mPanden.begin(), unspecifiedPand);

}

void HypotheekApplication::PandenToInifile()
{
	mInifile[L"panden"].Clear();
	for (size_t i = 0; i < mPanden.size(); ++i)
		mInifile[L"panden"][L"pand" + std::to_wstring(i)] = mPanden[i];

	mInifile[L"panden"][L"huidigpand"] = mPand;
}
