// geartestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "geartest.h"
#include "geartestDlg.h"
#include ".\geartestdlg.h"
#include "cameraParmFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace DShowLib;


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CgeartestDlg dialog



CgeartestDlg::CgeartestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CgeartestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


CgeartestDlg::~CgeartestDlg()
{
}

void CgeartestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTONIMAGESETTINGS, m_cButtonSettings);
	DDX_Control(pDX, IDC_BUTTONLIVEVIDEO, m_cButtonLive);
	DDX_Control(pDX, IDC_STATICVIDEOBIG, m_cStaticVideoWindowBig);
	DDX_Control(pDX, IDC_STATICVIDEOSMALL, m_cStaticVideoWindowSmall);
	DDX_Control(pDX, IDC_RADIO1, m_btnRadio1);
	DDX_Control(pDX, IDC_RADIO2, m_btnRadio2);
	DDX_Control(pDX, IDC_RADIO3, m_btnRadio3);
	DDX_Control(pDX, IDC_RADIO4, m_btnRadio4);
}

// CgeartestDlg message handlers

BEGIN_MESSAGE_MAP(CgeartestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP


	
	ON_BN_CLICKED(IDC_BUTTONIMAGESETTINGS, OnBnClickedButtonimagesettings)
	ON_BN_CLICKED(IDC_BUTTONLIVEVIDEO, OnBnClickedButtonlivevideo)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO2, &CgeartestDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CgeartestDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CgeartestDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO1, &CgeartestDlg::OnBnClickedRadio1)
END_MESSAGE_MAP()



BOOL CgeartestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	// Resize the video window to 640*480 pixels.
	m_cStaticVideoWindowBig.SetWindowPos(NULL,0,0,640,480,SWP_NOMOVE|SWP_NOZORDER);
	m_cStaticVideoWindowSmall.SetWindowPos(NULL,0,0,640,480,SWP_NOMOVE|SWP_NOZORDER);

	myCameraInit();
	OnBnClickedRadio1();
	return TRUE;  // return TRUE unless you set the focus to a control.
}

void CgeartestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}
//////////////////////////////////////////////////////////////////////////
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon. For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//////////////////////////////////////////////////////////////////////////

void CgeartestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle.
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
		CDialog::OnPaint();
	}
}
//////////////////////////////////////////////////////////////////////////
// The system calls this function to obtain the cursor to display while
// the user dragsthe minimized window.
//////////////////////////////////////////////////////////////////////////

HCURSOR CgeartestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
// Show the device select dialog, if the "Device" button has been clicked.
// If live video is displayed, it has to be stopped.
//////////////////////////////////////////////////////////////////////////


void CgeartestDlg::OnBnClickedButtondevice()
{
	int cameraNumber = 2;
	for (int i = 0; i < cameraNumber; ++i)
	{
		// If live video is running, stop it.
		pProcessThread = pProcessThreadArray[i];
		pProcessThread->OnLive(false);
		pProcessThread->m_cGrabber.showDevicePage(this->m_hWnd);
		pProcessThread->OnLive(true);
	}
}


//////////////////////////////////////////////////////////////////////////
// Show the image settings dialog of IC Imaging Control. 
//////////////////////////////////////////////////////////////////////////

void CgeartestDlg::OnBnClickedButtonimagesettings()
{
	int cameraNumber = 2;
	for(int i = 0; i < cameraNumber; ++i)
	{
		pProcessThread = pProcessThreadArray[i];
		bool flag = pProcessThread->m_cGrabber.isDevValid();
		if (flag)
		{
			//pProcessThread->OnLive(false);
			pProcessThread->m_cGrabber.showVCDPropertyPage();
			pProcessThread->m_cGrabber.saveDeviceStateToFile(PREDEF_CAMERAPARAMFILE[i]);
			//pProcessThread->OnLive(true);
		}	
	}
}


//////////////////////////////////////////////////////////////////////////
// This method starts and stops the live video.
//////////////////////////////////////////////////////////////////////////

void CgeartestDlg::OnBnClickedButtonlivevideo()
{
	int cameraNumber = 2;
	for(int i = 0; i < cameraNumber; ++i)
	{
		pProcessThread = pProcessThreadArray[i];
		bool flag = pProcessThread->m_cGrabber.isDevValid();
		if (flag)
		{
			bool flag1 = pProcessThread->m_cGrabber.isLive();
			if (flag1)
			{
				pProcessThread->OnLive(false);
				m_cButtonLive.SetWindowText(_T("Live Start"));
			}
			else
			{
				pProcessThread->OnLive(true);
				m_cButtonLive.SetWindowText(_T("Live Stop"));
			}

		}
	}
}


//////////////////////////////////////////////////////////////////////////

void CgeartestDlg::OnClose()
{
	int cameraNumber = 2;
	for(int i = 0; i < cameraNumber; ++i)
	{
		pProcessThread = pProcessThreadArray[i];
		pProcessThread->OnLive(false);
	}

	CDialog::OnClose();
}


int CgeartestDlg::myCameraInit(void)
{
	//camera init
	DShowLib::Grabber		grabber; 
	Grabber::tVidCapDevListPtr pVidCapDevList = grabber.getAvailableVideoCaptureDevices();
	if (pVidCapDevList == 0|| pVidCapDevList->empty())
	{
		MessageBox(_T("未发现有相机连接到本系统，请仔细检查后重试！！！"),_T("警告"),MB_OKCANCEL|MB_ICONWARNING);
		return 0;
	}

	int cameraNumber = 2;
	for (int i = 0;i < cameraNumber; ++i)
	{
		pProcessThreadArray[i] = new CProcessThread();
		pProcessThread= pProcessThreadArray[i];
		pProcessThread->CreateThread(CREATE_SUSPENDED);
		pProcessThread->SetThreadPriority(THREAD_PRIORITY_NORMAL);
		// 线程编号标识，偶数编号的线程用于处理大齿轮，奇数编号用于处理小齿轮
		pProcessThread->m_cameraIndex = i;
		if (i%2)
		{
			// Small
			pProcessThread->pShowStatic = &m_cStaticVideoWindowSmall;
		}
		else
		{
			//big
			pProcessThread->pShowStatic = &m_cStaticVideoWindowBig;
		}

		pProcessThread->ResumeThread();
	}
	return 0;
}

void CgeartestDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	bool flag = InitShapeModel(BLUE_TYPE_01);
	if (!flag )
		return;

	m_btnRadio1.SetForeColor(RGB(255,0,0));
	m_btnRadio1.SetBkColor(RGB(0,255,0));

	m_btnRadio2.SetForeColor(RGB(0,0,0));
	m_btnRadio2.SetBkColor(RGB(240,240,240));

	m_btnRadio3.SetForeColor(RGB(0,0,0));
	m_btnRadio3.SetBkColor(RGB(240,240,240));

	m_btnRadio4.SetForeColor(RGB(0,0,0));
	m_btnRadio4.SetBkColor(RGB(240,240,240));
}

void CgeartestDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	bool flag = InitShapeModel(BLUE_TYPE_02);
	if (!flag )
		return;

	m_btnRadio2.SetForeColor(RGB(255,0,0));
	m_btnRadio2.SetBkColor(RGB(0,255,0));

	m_btnRadio1.SetForeColor(RGB(0,0,0));
	m_btnRadio1.SetBkColor(RGB(240,240,240));

	m_btnRadio3.SetForeColor(RGB(0,0,0));
	m_btnRadio3.SetBkColor(RGB(240,240,240));

	m_btnRadio4.SetForeColor(RGB(0,0,0));
	m_btnRadio4.SetBkColor(RGB(240,240,240));
}


void CgeartestDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	bool flag = InitShapeModel(YELLOW_TYPE_01);
	if (!flag )
		return;

	m_btnRadio3.SetForeColor(RGB(255,0,0));
	m_btnRadio3.SetBkColor(RGB(0,255,0));

	m_btnRadio1.SetForeColor(RGB(0,0,0));
	m_btnRadio1.SetBkColor(RGB(240,240,240));

	m_btnRadio2.SetForeColor(RGB(0,0,0));
	m_btnRadio2.SetBkColor(RGB(240,240,240));

	m_btnRadio3.SetForeColor(RGB(0,0,0));
	m_btnRadio3.SetBkColor(RGB(240,240,240));
}


void CgeartestDlg::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	bool flag = InitShapeModel(YELLOW_TYPE_02);
	if (!flag )
		return;

	m_btnRadio4.SetForeColor(RGB(255,0,0));
	m_btnRadio4.SetBkColor(RGB(0,255,0));

	m_btnRadio1.SetForeColor(RGB(0,0,0));
	m_btnRadio1.SetBkColor(RGB(240,240,240));

	m_btnRadio2.SetForeColor(RGB(0,0,0));
	m_btnRadio2.SetBkColor(RGB(240,240,240));

	m_btnRadio3.SetForeColor(RGB(0,0,0));
	m_btnRadio3.SetBkColor(RGB(240,240,240));
}


bool CgeartestDlg::InitShapeModel(int gearType)
{
	bool sucess = true;
	int cameraNumber = 2;
	for (int i = 0; i < cameraNumber; ++i)
	{
		pProcessThread = pProcessThreadArray[i];
		pProcessThread->OnLive(false);
		bool flag = pProcessThread->InitShapeModel(gearType);// 载入新模板
		pProcessThread->OnLive(true);

		sucess = sucess && flag;
	}
	return sucess;
}


int CgeartestDlg::InitEditControl(void)
{
	int FontHeight = 200;
	//m_btnRadio1.SetTextFont(FontHeight,_T("黑体"));
	return 0;
}

