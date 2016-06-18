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

// 大齿轮计数，单个相机时只使用下面三个变量
int totalNumBig = 0;
int unqualNumBig = 0;

// 小齿轮计数，双相机时使用
int totalNumSmall = 0;
int unqualNumSmall = 0;

CString errorPos = _T("");

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
	, m_errorPos(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_TotalBig = 0;
	m_TotalSmall = 0;
	m_UnqualBig = 0;
	m_UnqualSmall = 0;
	
	m_UnqualRateBig = 0.0;
	m_UnqualRateSmall = 0.0;
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

	DDX_Control(pDX, IDC_EDIT_TOTAL_BIG_TEXT, m_sttTotalBig);
	DDX_Control(pDX, IDC_EDIT_UNQUALIFIED_BIG_TEXT, m_sttUnqualBig);
	DDX_Control(pDX, IDC_EDIT_UNQUALIFIED_RATE_BIG_TEXT, m_sttUnqualRateBig);
	DDX_Control(pDX, IDC_EDIT_TOTAL_SMALL_TEXT, m_sttTotalSmall);
	DDX_Control(pDX, IDC_EDIT_UNQUALIFIED_SMALL_TEXT, m_sttUnqualSmall);
	DDX_Control(pDX, IDC_EDIT_UNQUALIFIED_RATE_SMALL_TEXT, m_sttUnqualRateSmall);

	DDX_Control(pDX, IDC_EDIT_TOTAL_BIG, m_edtTotalBig);
	DDX_Control(pDX, IDC_EDIT_UNQUALIFIED_BIG, m_edtUnqualBig);
	DDX_Control(pDX, IDC_EDIT_UNQUALIFIED_RATE_BIG,m_edtUnqualRateBig);
	DDX_Control(pDX, IDC_EDIT_TOTAL_SMALL, m_edtTotalSmall);
	DDX_Control(pDX, IDC_EDIT_UNQUALIFIED_SMALL, m_edtUnqualSmall);
	DDX_Control(pDX, IDC_EDIT_UNQUALIFIED_RATE_SMALL,m_edtUnqualRateSmall);

	DDX_Text(pDX, IDC_EDIT_TOTAL_BIG, m_TotalBig);
	DDX_Text(pDX, IDC_EDIT_UNQUALIFIED_BIG, m_UnqualBig);
	DDX_Text(pDX, IDC_EDIT_UNQUALIFIED_RATE_BIG,m_UnqualRateBig);
	DDX_Text(pDX, IDC_EDIT_TOTAL_SMALL, m_TotalSmall);
	DDX_Text(pDX, IDC_EDIT_UNQUALIFIED_SMALL, m_UnqualSmall);
	DDX_Text(pDX, IDC_EDIT_UNQUALIFIED_RATE_SMALL,m_UnqualRateSmall);
	DDX_Text(pDX, IDC_EDIT_ERRORPOS, m_errorPos);
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
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CgeartestDlg::OnBnClickedButton1)
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

	InitEditControl();
	// Resize the video window to 640*480 pixels.
	m_cStaticVideoWindowBig.SetWindowPos(NULL,0,0,640,480,SWP_NOMOVE|SWP_NOZORDER);
	m_cStaticVideoWindowSmall.SetWindowPos(NULL,0,0,640,480,SWP_NOMOVE|SWP_NOZORDER);

	myCameraInit();
	OnBnClickedRadio1();
	OnBnClickedButtonlivevideo();
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
	for (int i = 0; i < m_cameraNumber; ++i)
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
	
	for(int i = 0; i < m_cameraNumber; ++i)
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
	for(int i = 0; i < m_cameraNumber; ++i)
	{
		pProcessThread = pProcessThreadArray[i];
		bool flag = pProcessThread->m_cGrabber.isDevValid();
		if (flag)
		{
			bool flag1 = pProcessThread->m_cGrabber.isLive();
			if (flag1)
			{
				pProcessThread->OnLive(false);
				KillTimer(1);
				m_cButtonLive.SetWindowText(_T("开始检测"));
			}
			else
			{
				pProcessThread->OnLive(true);
				SetTimer(1,0.5*1000,NULL);
				m_cButtonLive.SetWindowText(_T("停止检测"));
			}

		}
	}
}


//////////////////////////////////////////////////////////////////////////

void CgeartestDlg::OnClose()
{
	for(int i = 0; i < m_cameraNumber; ++i)
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

	m_cameraNumber = 2;// pVidCapDevList->size();

	for (int i = 0;i < m_cameraNumber; ++i)
	{
		pProcessThreadArray[i] = new CProcessThread();
		pProcessThread= pProcessThreadArray[i];
		pProcessThread->CreateThread(CREATE_SUSPENDED);
		pProcessThread->SetThreadPriority(THREAD_PRIORITY_NORMAL);
		// 线程编号标识，偶数编号的线程用于处理大齿轮，奇数编号用于处理小齿轮
		pProcessThread->m_cameraIndex = i;
		pProcessThread->pParentWnd = this;
		if (i%2)
		{
			// Small
			pProcessThread->m_IsBig = FALSE;
			pProcessThread->pShowStatic = &m_cStaticVideoWindowSmall;
		}
		else
		{
			//big
			pProcessThread->m_IsBig = TRUE;
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
	for (int i = 0; i < m_cameraNumber; ++i)
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
	// STATIC 空间初始化
	int sttFontHeight = 200;
	m_sttTotalBig.SetBkColor(RGB(255,255,200));
	m_sttTotalBig.SetForeColor(RGB(0,0,255));
	m_sttTotalBig.SetTextFont(sttFontHeight,_T("宋体"));
	m_sttTotalBig.SetWindowText(_T("总计"));

	m_sttUnqualBig.SetBkColor(RGB(255,255,200));
	m_sttUnqualBig.SetForeColor(RGB(0,0,255));
	m_sttUnqualBig.SetTextFont(sttFontHeight,_T("宋体"));
	m_sttUnqualBig.SetWindowText(_T("次品"));

	m_sttUnqualRateBig.SetBkColor(RGB(255,255,200));
	m_sttUnqualRateBig.SetForeColor(RGB(0,0,255));
	m_sttUnqualRateBig.SetTextFont(sttFontHeight,_T("宋体"));
	m_sttUnqualRateBig.SetWindowText(_T("次品率"));

	m_sttTotalSmall.SetBkColor(RGB(255,255,200));
	m_sttTotalSmall.SetForeColor(RGB(0,0,255));
	m_sttTotalSmall.SetTextFont(sttFontHeight,_T("宋体"));
	m_sttTotalSmall.SetWindowText(_T("总计"));

	m_sttUnqualSmall.SetBkColor(RGB(255,255,200));
	m_sttUnqualSmall.SetForeColor(RGB(0,0,255));
	m_sttUnqualSmall.SetTextFont(sttFontHeight,_T("宋体"));
	m_sttUnqualSmall.SetWindowText(_T("次品"));

	m_sttUnqualRateSmall.SetBkColor(RGB(255,255,200));
	m_sttUnqualRateSmall.SetForeColor(RGB(0,0,255));
	m_sttUnqualRateSmall.SetTextFont(sttFontHeight,_T("宋体"));
	m_sttUnqualRateSmall.SetWindowText(_T("次品率"));



	// EDIT 控件初始化
	int editFontHeight = 200;
	m_edtTotalBig.SetTextFont(editFontHeight,_T("宋体"));
	m_edtTotalBig.SetForeColor(RGB(0,0,255));
	m_edtTotalBig.SetBkColor(RGB(255,255,200));
	//m_edtTotalBig.SetWindowText(_T("001"));

	m_edtUnqualBig.SetTextFont(editFontHeight,_T("宋体"));
	m_edtUnqualBig.SetForeColor(RGB(0,0,255));
	m_edtUnqualBig.SetBkColor(RGB(255,255,200));
	//m_edtTotalBig.SetWindowText(_T("001"));

	m_edtUnqualRateBig.SetTextFont(editFontHeight,_T("宋体"));
	m_edtUnqualRateBig.SetForeColor(RGB(0,0,255));
	m_edtUnqualRateBig.SetBkColor(RGB(255,255,200));
	//m_edtTotalBig.SetWindowText(_T("001"));

	m_edtTotalSmall.SetTextFont(editFontHeight,_T("宋体"));
	m_edtTotalSmall.SetForeColor(RGB(0,0,255));
	m_edtTotalSmall.SetBkColor(RGB(255,255,200));
	//m_edtTotalBig.SetWindowText(_T("001"));

	m_edtUnqualSmall.SetTextFont(editFontHeight,_T("宋体"));
	m_edtUnqualSmall.SetForeColor(RGB(0,0,255));
	m_edtUnqualSmall.SetBkColor(RGB(255,255,200));
	//m_edtTotalBig.SetWindowText(_T("001"));

	m_edtUnqualRateSmall.SetTextFont(editFontHeight,_T("宋体"));
	m_edtUnqualRateSmall.SetForeColor(RGB(0,0,255));
	m_edtUnqualRateSmall.SetBkColor(RGB(255,255,200));
	//m_edtTotalBig.SetWindowText(_T("001"));


	// RADIO 控件初始化
	return 0;
}


void CgeartestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ

	m_TotalBig = totalNumBig;
	m_UnqualBig = unqualNumBig;
	m_UnqualRateBig = (float)unqualNumBig/totalNumBig;

	m_TotalSmall = totalNumSmall;
	m_UnqualSmall = unqualNumSmall;
	m_UnqualRateSmall = (float)unqualNumSmall/totalNumSmall;

	m_errorPos = errorPos;
	//SetDlgItemText(IDC_STATIC_ERRORPOS,m_errorPos);
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}


void CgeartestDlg::OnBnClickedButton1()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	totalNumBig = 0;
	unqualNumBig = 0;

	totalNumSmall = 0;
	unqualNumSmall = 0;

	errorPos = _T("");
	OnTimer(1);
}
