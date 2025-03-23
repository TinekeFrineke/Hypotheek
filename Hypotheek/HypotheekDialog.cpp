
// HypotheekDialog.cpp : implementation file
//

#include "pch.h"

#include "framework.h"
#include "HypotheekApplication.h"
#include "HypotheekDialog.h"
#include "resource.h"

#include <filesystem>

#include <Utilities/Inifile.h>

#include "afxdialogex.h"
#include "HypotheekOwner.h"
#include "InvoerDialog.h"
#include "NatasjaLastenDialog.h"
#include "OverviewDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// HypotheekDialog dialog



CHypotheekDialog::CHypotheekDialog(HypotheekApplication& application, Inifile& inifile, CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_HYPOTHEEK_DIALOG, pParent)
    , mApplication(application)
    , mInifile(inifile)
    , m_hypotheekOwner(std::make_shared<HypotheekOwner>(inifile))
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CHypotheekDialog::~CHypotheekDialog() = default;


void CHypotheekDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_HYPOTHEEK_TAB, mTabControl);
}

BEGIN_MESSAGE_MAP(CHypotheekDialog, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_DESTROY()
END_MESSAGE_MAP()


// HypotheekDialog message handlers

BOOL CHypotheekDialog::OnInitDialog()
{
    m_hypotheekOwner->VulPandenUitInifile();

    mTabControl.AddPage(new InvoerDialog(std::static_pointer_cast<IHypotheekOwner>(m_hypotheekOwner), mInifile, this), IDD_INVOER_DIALOG, L"Invoer");
    mTabControl.AddPage(new NatasjaLastenDialog(std::static_pointer_cast<IHypotheekOwner>(m_hypotheekOwner)/*mApplication*/, mInifile, this), IDD_LASTEN_NATASJA_DIALOG, L"Lasten Natasja");
    mTabControl.AddPage(new OverviewDialog(std::static_pointer_cast<IHypotheek>(m_hypotheekOwner)/*mApplication*/, mInifile, this), IDD_OVERVIEW_DIALOG, L"Overzicht");

    CDialogEx::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    mTabControl.Initialize();
    mTabControl.SelectPage(0);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHypotheekDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHypotheekDialog::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHypotheekDialog::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CHypotheekDialog::OnDestroy()
{
    m_hypotheekOwner->PandenToInifile();
    mInifile.Write();

    CDialogEx::OnDestroy();
}
